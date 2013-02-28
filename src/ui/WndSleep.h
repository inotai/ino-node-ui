#ifndef __UI_WND_SLEEP_H__
#define __UI_WND_SLEEP_H__

#include "ui/IWnd.h"

namespace ui {

	class Wnd;

	class WndSleep : public IWnd
	{
	public:
		WndSleep()
		:	m_style(0),
			m_style_ex(0)
		{}

		virtual ~WndSleep() {}

		virtual std::wstring getText()
		{ return m_text; }
		virtual bool setText(const std::wstring & text)
		{ m_text = text; return true; }

		virtual RectF getBounds()
		{ return m_bounds; }
		virtual bool setBounds(const RectF & bounds)
		{ m_bounds = bounds; return true; }

		virtual DWORD getStyle()
		{ return m_style; }
		virtual bool setStyle(DWORD style)
		{ m_style = style; return true; }
		
		virtual DWORD getStyleEx()
		{ return m_style_ex; }
		virtual bool setStyleEx(DWORD style_ex)
		{ m_style_ex = style_ex; return true; }

	private:
		std::wstring m_text;
		RectF m_bounds;
		DWORD m_style;
		DWORD m_style_ex;
	};

}

#endif // __UI_WND_SLEEP_H__