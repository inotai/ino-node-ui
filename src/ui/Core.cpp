#include "precompiled.h"

#include "ui/Factory.h"
#include "ui/Dispatcher.h"

#include "ui/Core.h"

namespace ui {

	Core::Core(HINSTANCE hinst)
	:	m_hinst(hinst)
	{
	}

	Core::~Core()
	{
	}

	void Core::initialize()
	{
		if (!SUCCEEDED(::OleInitialize(NULL)))
		{
			INO_NOT_REACHED();
		}
		InitCommonControls();

		m_dispatcher.reset(new Dispatcher);
		m_factory.reset(new Factory(this));

		m_dispatcher->init();
	}

	void Core::release()
	{
		::OleUninitialize();
	}

	void Core::quit()
	{
	}
}