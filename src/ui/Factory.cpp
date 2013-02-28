#include "precompiled.h"

#include "ui/Dispatcher.h"
#include "ui/Window.h"

#include "ui/Factory.h"

namespace ui {

	Factory::Factory(Core * core)
	:	m_core(core)
	{
	}

	Factory::~Factory()
	{
	}

	void Factory::registerClass(const std::wstring & class_name, Constructor constructor)
	{
		m_map.insert(std::make_pair(class_name, constructor));
	}

	shared_ptr<Wnd> Factory::create(const std::wstring & class_name)
	{
		Map::iterator it = m_map.find(class_name);
		if (it == m_map.end()) {
			return shared_ptr<Wnd>();
		}
		Constructor c = it->second;
		shared_ptr<Wnd> ret((*c)(m_core));
		return ret;
	}

}