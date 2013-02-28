#include "precompiled.h"

#include "ui/Dispatcher.h"
#include "ui/Factory.h"
#include "ui/Window.h"

#include "js/util.h"

#include "js/js.Window.h"

namespace js {

	ui::Dispatcher * Window::s_dispatcher = NULL;

	void Window::Init(v8::Handle<v8::Object> target, ui::Dispatcher * Dispatcher)
	{
		s_dispatcher = Dispatcher;
		// Prepare constructor template
		v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(New);
		tpl->SetClassName(v8::String::NewSymbol("Window"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		// Prototype
		tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("setBounds"),
			v8::FunctionTemplate::New(SetBounds)->GetFunction());
		tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("on"),
			v8::FunctionTemplate::New(On)->GetFunction());
		tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("close"),
			v8::FunctionTemplate::New(Close)->GetFunction());
		tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("wake"),
			v8::FunctionTemplate::New(Wake)->GetFunction());

		v8::Persistent<v8::Function> constructor = v8::Persistent<v8::Function>::New(tpl->GetFunction());

		target->Set(v8::String::NewSymbol("Window"), constructor);
	}


	v8::Handle<v8::Value> Window::New(const v8::Arguments & args)
	{
		v8::HandleScope scope;

		util::check_argument_count(args, 1);

		std::wstring title;
		util::read_arg_string(args, 0, &title);

		Window * window = new Window();
		window->m_window = s_dispatcher->getFactory()->createWindow(title);
		window->m_window->on_close.bind(window, &Window::_onClose);
		window->Wrap(args.This());

		window->Ref();

		return args.This();
	}

	Window::Window()
	:	m_window(NULL)
	{
	}

	Window::~Window()
	{

	}

	v8::Handle<v8::Value> Window::SetBounds(const v8::Arguments & args)
	{
		v8::HandleScope scope;

		util::check_argument_count(args, 4);

		double left;
		if (!util::read_arg_double(args, 0, &left)) {
			return v8::Undefined();
		}

		double top;
		if (!util::read_arg_double(args, 1, &top)) {
			return v8::Undefined();
		}

		double right;
		if (!util::read_arg_double(args, 2, &right)) {
			return v8::Undefined();
		}

		double bottom;
		if (!util::read_arg_double(args, 3, &bottom)) {
			return v8::Undefined();
		}

		Window * window = ObjectWrap::Unwrap<Window>(args.This());
		// bool ret = window->m_window->setBounds();
		bool ret = s_dispatcher->send<ui::traits::RectF, ui::traits::Boolean>(
			ui::RectF((ui::CoordF)left, (ui::CoordF)top, (ui::CoordF)right, (ui::CoordF)bottom),
			ino::make_delegate(window->m_window.get(), &ui::Wnd::setBounds)
			);

		return scope.Close(v8::Boolean::New(ret));
	}

	v8::Handle<v8::Value> Window::On(const v8::Arguments & args)
	{
		v8::HandleScope scope;

		util::check_argument_count(args, 2);

		std::wstring event_type;
		if (!util::read_arg_string(args, 0, &event_type)) {
			return v8::Undefined();
		}

		v8::Persistent<v8::Function> event_callback;
		if (!util::read_arg_function(args, 1, &event_callback)) {
			return v8::Undefined();
		}

		Window * window = ObjectWrap::Unwrap<Window>(args.This());
		window->m_event_map.insert(std::make_pair(event_type, event_callback));

		return v8::False();
	}

	v8::Handle<v8::Value> Window::Wake(const v8::Arguments & args)
	{
		v8::HandleScope scope;

		Window * window = ObjectWrap::Unwrap<Window>(args.This());
		// bool ret = window->m_window->setBounds();
		bool ret = s_dispatcher->send<ui::traits::Boolean, ui::traits::Boolean>(
			true,
			ino::make_delegate(window->m_window.get(), &ui::Wnd::wake_)
			);

		return scope.Close(v8::Boolean::New(ret));

	}

	v8::Handle<v8::Value> Window::Close(const v8::Arguments & args)
	{
		v8::HandleScope scope;

		Window * window = ObjectWrap::Unwrap<Window>(args.This());
		// bool ret = window->m_window->setBounds();
		bool ret = s_dispatcher->send<ui::traits::Integer, ui::traits::Boolean>(
			true,
			ino::make_delegate(window->m_window.get(), &ui::Wnd::close)
			);

		return scope.Close(v8::Boolean::New(ret));
	}

	//
	// Instance
	//

	bool Window::_onClose(ui::Wnd * wnd)
	{
		return s_dispatcher->_send<ui::traits::Wnd, ui::traits::Boolean>(wnd, ino::make_delegate(this, &Window::onClose));
	}

	bool Window::onClose(ui::Wnd * wnd)
	{
		v8::HandleScope scope;

		EventMap::iterator it = m_event_map.find(L"close");
		if (it != m_event_map.end())
		{
			v8::Handle<v8::Value> v_ret = it->second->Call(v8::Context::GetCurrent()->Global(), 0, NULL);
			if (v_ret.IsEmpty() || !v_ret->IsBoolean()) {
				return false;
			}
			return v_ret->BooleanValue();
		}
		return true;
	}
}