#ifndef __JS_HANDLE_H__
#define __JS_HANDLE_H__

namespace ui {
	class Core;
	class Wnd;
}

namespace js {

	class Wnd;

	class Handle : public node::ObjectWrap
	{
	public:
		static void Init(ui::Core * core);
		static v8::Handle<v8::Value> NewInstance(const v8::Arguments & args);

	private:
		static ui::Core * s_core;
		static v8::Persistent<v8::Function> s_constructor;
		static v8::Handle<v8::Value> New(const v8::Arguments & args);

	private:
		Handle(shared_ptr<ui::Wnd> handle);
		~Handle();

	public:
		shared_ptr<ui::Wnd> getHandle()
		{ return m_handle; }

	private:
		shared_ptr<ui::Wnd> m_handle;
		typedef std::multimap<std::wstring, v8::Persistent<v8::Function>, std::less<std::wstring>> EventMap;
		EventMap m_event_map;
	};

}

#endif // __JS_HANDLE_H__