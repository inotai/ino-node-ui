#include "precompiled.h"

#include "ui/Core.h"
#include "ui/Factory.h"

#include "js/js.Handle.h"
#include "js/js.view.h"

uv_async_t async_keeper;
HINSTANCE hinst;
shared_ptr<ui::Core> s_core;

// --------------------------------------------------------------------------
void on_keeper(uv_async_t * handle, int status)
// --------------------------------------------------------------------------
{
	std::cout << "onKeeper" << std::endl;
	uv_close((uv_handle_t*)&async_keeper, NULL);
}

// --------------------------------------------------------------------------
static v8::Handle<v8::Value> quit(const v8::Arguments & args)
// --------------------------------------------------------------------------
{
	s_core->quit();
	return v8::True();
}

// For constructors
#include "ui/Window.h"
#include "ui/Button.h"

extern "C" {
	static void init(v8::Handle<v8::Object> target)
	{
		v8::HandleScope scope;

		// Core
		s_core.reset(new ui::Core(hinst));
		s_core->initialize();

		// Factory
		ui::Factory * factory = s_core->getFactory();
		factory->registerClass(L"Window", ui::Window::constructor);
		factory->registerClass(L"Button", ui::Button::constructor);

		js::Handle::Init(s_core.get());
		js::view::Init(target, s_core.get());

		// Keeper
		uv_async_init(uv_default_loop(), &async_keeper, on_keeper);
		
		NODE_SET_METHOD(target, "quit", &quit);
	}
}

NODE_MODULE(ui_native, init);

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason,
		 LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		hinst = hinstDLL;
	}

	return TRUE;
}