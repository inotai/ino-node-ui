#ifndef __JS_WND_H__
#define __JS_WND_H__

namespace ui {
	class Core;
}

namespace js {

	class view
	{
	public:
		// Initializes the API.
		static void Init(v8::Handle<v8::Object> target, ui::Core * core);

	private:
		static ui::Core * s_core;

		static v8::Handle<v8::Value> Create(const v8::Arguments & args);
		static v8::Handle<v8::Value> Wake(const v8::Arguments & args);
		static v8::Handle<v8::Value> Sleep(const v8::Arguments & args);
		static v8::Handle<v8::Value> AddChild(const v8::Arguments & args);
		static v8::Handle<v8::Value> SetBounds(const v8::Arguments & args);
	};

}

#endif // __JS_WND_H__