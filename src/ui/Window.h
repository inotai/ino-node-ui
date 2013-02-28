#ifndef __UI_WINDOW_H__
#define __UI_WINDOW_H__

#include "ui/Wnd.h"

namespace ui {

	class Window : public Wnd
	{
	public:
		static Wnd * constructor(Core * core)
		{
			return new Window(core);
		};

		Window(Core * core)
		:	Wnd(core, L"ui.Window")
		{
			setStyle(WS_OVERLAPPEDWINDOW);
		}

		virtual ~Window()
		{
		}

		virtual void initClass(WNDCLASSEX * wc)
		{
			wc->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		}
	};

}

#endif // __UI_WINDOW_H__