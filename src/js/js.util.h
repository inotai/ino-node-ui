#ifndef __JS_HELPER_H__
#define __JS_HELPER_H__

namespace js {

	struct util
	{
	public:
		/// Generic error
		static void error(const std::wstring & message)
		{
			ThrowException(v8::Exception::Error(v8::String::New((uint16_t*)message.c_str())));
		}


		static void error_argument_type(int index, const wchar_t * expected)
		{
			std::wstring m = ino::util::format(L"Argument %d must be %s", index + 1, expected);
			ThrowException(v8::Exception::TypeError(v8::String::New((uint16_t*)m.c_str())));
		}

		static void error_argument_count(int expected, int actual)
		{
			std::wstring m = ino::util::format(L"Wrong number of arguments (%d expected, %d given).", expected, actual);
			ThrowException(v8::Exception::TypeError(v8::String::New((uint16_t*)m.c_str())));
		}

		static bool check_argument_count(const v8::Arguments & args, int expected)
		{
			if (args.Length() != expected)
			{
				error_argument_count(expected, args.Length());
				return false;
			}
			return true;
		}

		static bool read_arg_uint32(const v8::Arguments & args, int index, uint32_t * o_int)
		{
			if (args[index]->IsUint32()) {
				*o_int = args[index]->Uint32Value();
				return true;
			} else {
				error_argument_type(index, L"uint32");
			}
			return false;
		}

		static bool read_arg_int64(const v8::Arguments & args, int index, int64_t * o_int)
		{
			if (args[index]->IsNumber()) {
				*o_int = args[index]->IntegerValue();
				return true;
			} else {
				error_argument_type(index, L"int64");
			}
			return false;
		}

		static bool read_arg_double(const v8::Arguments & args, int index, double * o_double)
		{
			if (args[index]->IsNumber()) {
				*o_double = args[index]->NumberValue();
				return true;
			} else {
				error_argument_type(index, L"double");
			}
			return false;
		}

		static bool read_arg_string(const v8::Arguments & args, int index, std::wstring * o_string)
		{
			if (args[index]->IsString()) {
				v8::String::Value v(v8::Local<v8::String>::Cast(args[index]));
				o_string->assign(reinterpret_cast<wchar_t*>(*v), v.length());
				return true;
			} else {
				error_argument_type(index, L"string");
			}
			return false;
		}

		static bool read_arg_array(const v8::Arguments & args, int index, v8::Local<v8::Array> * o_array)
		{
			if (args[index]->IsArray()) {
				*o_array = v8::Local<v8::Array>::Cast(args[index]);
				return true;
			} else {
				error_argument_type(index, L"Array");
			}
			return false;
		}

		static bool read_arg_object(const v8::Arguments & args, int index, v8::Local<v8::Object> * o_object)
		{
			if (args[index]->IsObject()) {
				*o_object = v8::Local<v8::Object>::Cast(args[index]);
				return true;
			} else {
				error_argument_type(index, L"Object");
			}
			return false;
		}

		static bool read_arg_function(const v8::Arguments & args, int index, v8::Local<v8::Function> * o_function)
		{
			if (args[index]->IsFunction()) {
				*o_function = v8::Local<v8::Function>::Cast(args[index]);
				return true;
			} else {
				error_argument_type(index, L"function");
			}
			return false;
		}

		static bool read_arg_function(const v8::Arguments & args, int index, v8::Persistent<v8::Function> * o_function)
		{
			v8::Local<v8::Function> lfn;
			if (read_arg_function(args, index, &lfn)) {
				*o_function = v8::Persistent<v8::Function>::New(lfn);
				return true;
			}
			return false;
		}

		static void report_exception(v8::TryCatch & try_catch)
		{
		  v8::HandleScope scope;

		  display_exception_line(try_catch);

		  v8::String::Utf8Value trace(try_catch.StackTrace());

		  // range errors have a trace member set to undefined
		  if (trace.length() > 0 && !try_catch.StackTrace()->IsUndefined()) {
			fprintf(stderr, "%s\n", *trace);
		  } else {
			// this really only happens for RangeErrors, since they're the only
			// kind that won't have all this info in the trace, or when non-Error
			// objects are thrown manually.
			v8::Local<v8::Value> er = try_catch.Exception();
			bool isErrorObject = er->IsObject() &&
			  !(er->ToObject()->Get(v8::String::New("message"))->IsUndefined()) &&
			  !(er->ToObject()->Get(v8::String::New("name"))->IsUndefined());

			if (isErrorObject) {
			  v8::String::Utf8Value name(er->ToObject()->Get(v8::String::New("name")));
			  fprintf(stderr, "%s: ", *name);
			}

			v8::String::Utf8Value msg(!isErrorObject ? er
								 : er->ToObject()->Get(v8::String::New("message")));
			fprintf(stderr, "%s\n", *msg);
		  }

		  fflush(stderr);
		}

	private:
		static void display_exception_line(v8::TryCatch &try_catch) {
		  // Prevent re-entry into this function.  For example, if there is
		  // a throw from a program in vm.runInThisContext(code, filename, true),
		  // then we want to show the original failure, not the secondary one.
		  static bool displayed_error = false;

		  if (displayed_error) return;
		  displayed_error = true;

		  v8::HandleScope scope;

		  v8::Handle<v8::Message> message = try_catch.Message();

		  uv_tty_reset_mode();

		  fprintf(stderr, "\n");

		  if (!message.IsEmpty()) {
			// Print (filename):(line number): (message).
			v8::String::Utf8Value filename(message->GetScriptResourceName());
			const char* filename_string = *filename;
			int linenum = message->GetLineNumber();
			fprintf(stderr, "%s:%i\n", filename_string, linenum);
			// Print line of source code.
			v8::String::Utf8Value sourceline(message->GetSourceLine());
			const char* sourceline_string = *sourceline;

			// Because of how node modules work, all scripts are wrapped with a
			// "function (module, exports, __filename, ...) {"
			// to provide script local variables.
			//
			// When reporting errors on the first line of a script, this wrapper
			// function is leaked to the user. There used to be a hack here to
			// truncate off the first 62 characters, but it caused numerous other
			// problems when vm.runIn*Context() methods were used for non-module
			// code.
			//
			// If we ever decide to re-instate such a hack, the following steps
			// must be taken:
			//
			// 1. Pass a flag around to say "this code was wrapped"
			// 2. Update the stack frame output so that it is also correct.
			//
			// It would probably be simpler to add a line rather than add some
			// number of characters to the first line, since V8 truncates the
			// sourceline to 78 characters, and we end up not providing very much
			// useful debugging info to the user if we remove 62 characters.

			int start = message->GetStartColumn();
			int end = message->GetEndColumn();

			// fprintf(stderr, "---\nsourceline:%s\noffset:%d\nstart:%d\nend:%d\n---\n", sourceline_string, start, end);

			fprintf(stderr, "%s\n", sourceline_string);
			// Print wavy underline (GetUnderline is deprecated).
			for (int i = 0; i < start; i++) {
			  fputc((sourceline_string[i] == '\t') ? '\t' : ' ', stderr);
			}
			for (int i = start; i < end; i++) {
			  fputc('^', stderr);
			}
			fputc('\n', stderr);
		  }
		}

	};
}

#endif // __JS_HELPER_H__