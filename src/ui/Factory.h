#ifndef __UI_FACTORY_H__
#define __UI_FACTORY_H__

#include "ui/Message.h"

namespace ui {

	class Core;
	class Wnd;

	class Factory
	{
	public:
		Factory(Core * core);
		~Factory();

		typedef Wnd* (*Constructor)(Core *);
		void registerClass(const std::wstring & class_name, Constructor constructor);

		shared_ptr<Wnd> create(const std::wstring & class_name);

	private:
		Core * m_core;

		typedef std::map<std::wstring, Constructor> Map;
		Map m_map;
	};

}

#endif // __UI_FACTORY_H__