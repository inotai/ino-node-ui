#ifndef __JS_WINDOW_H__
#define __JS_WINDOW_H__

namespace ui {
	class Wnd;
	class Factory;
}

namespace js {

	class Window : public node::ObjectWrap
	{
	public:
		static void Init(v8::Handle<v8::Object> target, ui::Dispatcher * Dispatcher);

	private:
		Window();
		~Window();

		static v8::Handle<v8::Value> New(const v8::Arguments & args);
		static v8::Handle<v8::Value> SetBounds(const v8::Arguments & args);
		static v8::Handle<v8::Value> On(const v8::Arguments & args);
		static v8::Handle<v8::Value> Wake(const v8::Arguments & args);
		static v8::Handle<v8::Value> Close(const v8::Arguments & args);

		static ui::Dispatcher * s_dispatcher;
		shared_ptr<ui::Window> m_window;

		bool _onClose(ui::Wnd * wnd);
		bool onClose(ui::Wnd * wnd);

		typedef std::multimap<std::wstring, v8::Persistent<v8::Function>, std::less<std::wstring>> EventMap;
		EventMap m_event_map;
	};

}

#endif // __JS_WINDOW_H__