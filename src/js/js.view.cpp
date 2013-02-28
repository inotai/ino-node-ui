#include "precompiled.h"

#include "ui/Core.h"
#include "ui/Dispatcher.h"
#include "ui/Wnd.h"

#include "js/js.util.h"
#include "js/js.Handle.h"

#include "js/js.view.h"

namespace js {
	
	ui::Core * view::s_core = NULL;

	void view::Init(v8::Handle<v8::Object> target, ui::Core * core)
	{
		s_core = core;

		v8::Persistent<v8::Object> obj(v8::Object::New());

		NODE_SET_METHOD(obj, "create", &view::Create);
		NODE_SET_METHOD(obj, "wake", &view::Wake);
		NODE_SET_METHOD(obj, "setBounds", &view::SetBounds);
		NODE_SET_METHOD(obj, "addChild", &view::AddChild);

		target->Set(v8::String::NewSymbol("view"), obj);
	}

	v8::Handle<v8::Value> view::Create(const v8::Arguments & args)
	{
		v8::HandleScope scope;
		return scope.Close(Handle::NewInstance(args));
	}

	v8::Handle<v8::Value> view::Wake(const v8::Arguments & args)
	{
		v8::HandleScope scope;

		if (!util::check_argument_count(args, 1)) {
			return scope.Close(v8::Undefined());
		}

		v8::Local<v8::Object> obj;
		if (!util::read_arg_object(args, 0, &obj)) {
			return scope.Close(v8::Undefined());
		}

		Handle * handle = node::ObjectWrap::Unwrap<Handle>(obj);
		bool ret = s_core->getDispatcher()->send<ui::traits::Boolean, ui::traits::Boolean>(
			true,
			ino::make_delegate(handle->getHandle().get(), &ui::Wnd::wake_)
			);

		return scope.Close(v8::Boolean::New(ret));
	}

	v8::Handle<v8::Value> view::SetBounds(const v8::Arguments & args)
	{
		v8::HandleScope scope;

		util::check_argument_count(args, 5);

		v8::Local<v8::Object> obj;
		if (!util::read_arg_object(args, 0, &obj)) {
			return scope.Close(v8::Undefined());
		}

		Handle * handle = node::ObjectWrap::Unwrap<Handle>(obj);

		double left;
		if (!util::read_arg_double(args, 1, &left)) {
			return v8::Undefined();
		}

		double top;
		if (!util::read_arg_double(args, 2, &top)) {
			return v8::Undefined();
		}

		double right;
		if (!util::read_arg_double(args, 3, &right)) {
			return v8::Undefined();
		}

		double bottom;
		if (!util::read_arg_double(args, 4, &bottom)) {
			return v8::Undefined();
		}

		// bool ret = window->m_window->setBounds();
		bool ret = s_core->getDispatcher()->send<ui::traits::RectF, ui::traits::Boolean>(
			ui::RectF((ui::CoordF)left, (ui::CoordF)top, (ui::CoordF)right, (ui::CoordF)bottom),
			ino::make_delegate(handle->getHandle().get(), &ui::Wnd::setBounds)
			);

		return scope.Close(v8::Boolean::New(ret));
	}

	v8::Handle<v8::Value> view::AddChild(const v8::Arguments & args)
	{
		v8::HandleScope scope;

		if (!util::check_argument_count(args, 2)) {
			return scope.Close(v8::Undefined());
		}

		v8::Local<v8::Object> obj;
		if (!util::read_arg_object(args, 0, &obj)) {
			return scope.Close(v8::Undefined());
		}

		v8::Local<v8::Object> obj_child;
		if (!util::read_arg_object(args, 1, &obj_child)) {
			return scope.Close(v8::Undefined());
		}

		Handle * handle = node::ObjectWrap::Unwrap<Handle>(obj);
		Handle * handle_child = node::ObjectWrap::Unwrap<Handle>(obj_child);

		bool ret = s_core->getDispatcher()->send<ui::traits::WndSharedPtr, ui::traits::Boolean>(
			handle_child->getHandle(),
			ino::make_delegate(handle->getHandle().get(), &ui::Wnd::addChild_)
			);

		return scope.Close(v8::Boolean::New(ret));
	}

}