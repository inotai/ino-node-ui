#ifndef __UI_IWND_H__
#define __UI_IWND_H__

namespace ui {

	class Wnd;

	class IWnd
	{
	public:
		virtual ~IWnd() {};

		virtual std::wstring getText() = 0;
		virtual bool setText(const std::wstring & text) = 0;
		virtual RectF getBounds() = 0;
		virtual bool setBounds(const RectF & bounds) = 0;
		virtual DWORD getStyle() = 0;
		virtual bool setStyle(DWORD style) = 0;
		virtual DWORD getStyleEx() = 0;
		virtual bool setStyleEx(DWORD style_ex) = 0;
	};


}

#endif // __UI_IWND_H__