#ifndef __UI_WND_WAKE_H__
#define __UI_WND_WAKE_H__

#include "ui/IWnd.h"
#include "ui/Message.h"

namespace ui {
	
	class Wnd;
	class WndSleep;
	class Msg;

	class WndWake : public IWnd
	{
	public:
		WndWake(Wnd * wnd);
		virtual ~WndWake();

		void wake();
		void sleep(WndSleep * wnd_sleep);
		
		virtual std::wstring getText();
		virtual bool setText(const std::wstring & text);
		virtual RectF getBounds();
		virtual bool setBounds(const RectF & bounds);
		virtual DWORD getStyle();
		virtual bool setStyle(DWORD style);
		virtual DWORD getStyleEx();
		virtual bool setStyleEx(DWORD style_ex);

		bool close(int ret);
		void destroy();

		bool create(const std::wstring & title, const RectF & rect);
		bool create_(const tuple<std::wstring, RectF> & params)
		{ return create(std::get<0>(params), std::get<1>(params)); }

		HWND getHWND() const
		{ return m_hwnd; }
		
		static WndWake * getFromHWND(HWND hwnd);
		void attachToHWND(HWND hwnd);
		void detachFromHWND(HWND hwnd);

	protected:
		virtual bool handleMessage(Msg * io_msg);
		void callDefaultWNDPROC(Msg * io_msg);
		void callWNDPROC(Msg * io_msg, WNDPROC wnd_proc);

	private:
		Wnd * m_wnd;
		HWND m_hwnd;

		static LRESULT CALLBACK _proc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
	};

}

#endif // __UI_WND_INSTANCE_H__