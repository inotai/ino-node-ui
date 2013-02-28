#include "precompiled.h"

#include "ui/Core.h"
#include "ui/Dispatcher.h"
#include "ui/Factory.h"
#include "ui/Window.h"

#include "js/js.util.h"

#include "js/js.Handle.h"

namespace js {

	ui::Core * Handle::s_core = NULL;
	v8::Persistent<v8::Function> Handle::s_constructor;

	void Handle::Init(ui::Core * core)
	{
		s_core = core;
		// Prepare constructor template
		v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(New);
		tpl->SetClassName(v8::String::NewSymbol("Handle"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		s_constructor = v8::Persistent<v8::Function>::New(tpl->GetFunction());
	}

	v8::Handle<v8::Value> Handle::NewInstance(const v8::Arguments & args)
	{
		v8::HandleScope scope;

		util::check_argument_count(args, 1);

		std::wstring class_name;
		if (!args[0]->IsString()) {
			util::error_argument_type(0, L"string");
			return scope.Close(v8::Undefined());
		}

		v8::Handle<v8::Value> argv[1] = { args[0] };
		v8::Local<v8::Object> instance = s_constructor->NewInstance(1, argv);
		return scope.Close(instance);
	}


	v8::Handle<v8::Value> Handle::New(const v8::Arguments & args)
	{
		v8::HandleScope scope;

		util::check_argument_count(args, 1);

		std::wstring class_name;
		if (!util::read_arg_string(args, 0, &class_name)) {
			return scope.Close(v8::Undefined());
		}

		shared_ptr<ui::Wnd> wnd = s_core->getFactory()->create(class_name);
		if (wnd == NULL) {
			util::error(ino::util::format(L"Unknown class `%s`", class_name.c_str()));
			return v8::Undefined();
		}

		Handle * handle = new Handle(wnd);
		handle->Wrap(args.This());
		handle->Ref();

		return scope.Close(args.This());
	}

	Handle::Handle(shared_ptr<ui::Wnd> handle)
	:	m_handle(handle)
	{
	}

	Handle::~Handle()
	{

	}
}