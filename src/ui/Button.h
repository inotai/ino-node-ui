#ifndef __UI_BUTTON_H__
#define __UI_BUTTON_H__

#include "ui/Wnd.h"

namespace ui {

	class Button : public Wnd
	{
	public:
		static Wnd * constructor(Core * core)
		{
			return new Button(core);
		};

		Button(Core * core)
		:	Wnd(core, L"Button")
		{
			setStyle(WS_CHILD | WS_VISIBLE | WS_TABSTOP);
			setText(L"Button");
		}

		virtual ~Button()
		{
		}
	};

}

#endif // __UI_BUTTON_H__