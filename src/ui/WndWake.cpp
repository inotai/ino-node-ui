#include "precompiled.h"

#include "ui/util.h"
#include "ui/Dispatcher.h"
#include "ui/Wnd.h"
#include "ui/Msg.h"

#include "ui/WndWake.h"

namespace ui {

	WndWake::WndWake(Wnd * wnd)
	:	m_hwnd(NULL),
		m_wnd(wnd)
	{
	}

	WndWake::~WndWake()
	{
	}

	void WndWake::wake()
	{
		WNDCLASSEX wnd_class;
		if (::GetClassInfoExW(m_wnd->getInstance(), m_wnd->getClassName().c_str(), &wnd_class) == FALSE)
		{
			ZeroMemory(&wnd_class, sizeof(WNDCLASSEX));
			
			m_wnd->initClass(&wnd_class);

			// Do this after we call initClass so it cannot be overwritten.
			wnd_class.cbSize = sizeof(WNDCLASSEX);
			wnd_class.lpfnWndProc = &WndWake::_proc;
			wnd_class.hInstance = m_wnd->getInstance();
			wnd_class.lpszClassName = m_wnd->getClassName().c_str();

			if (!::RegisterClassExW(&wnd_class))
			{
				util::log_error(L"::RegisterClass", ::GetLastError());
				INO_NOT_REACHED();
			}
		}

		HWND hwnd_parent = HWND_DESKTOP;
		if (m_wnd->getParent() != NULL) {
			INO_ASSERT(m_wnd->getParent()->getWake() != NULL);
			INO_ASSERT(m_wnd->getParent()->getWake()->getHWND() != NULL);
			hwnd_parent = m_wnd->getParentHWND();
		}

		RectF bounds = m_wnd->getBounds();
		m_hwnd = ::CreateWindowExW
			(
			// Style Ex
			m_wnd->getStyleEx(),
			// Class name
			m_wnd->getClassName().c_str(),
			// Title
			m_wnd->getText().c_str(),
			// Style
			m_wnd->getStyle(),
			// Position
			util::to_i(bounds.left), util::to_i(bounds.top),
			// Size
			util::to_i(bounds.getWidth()), util::to_i(bounds.getHeight()),
			// Parent
			hwnd_parent,
			// Menu
			NULL,
			// Instance
			m_wnd->getInstance(),
			// Special parameters
			(LPVOID)this
			);

		::ShowWindow(m_hwnd, SW_SHOW);
	}

	void WndWake::sleep(WndSleep * wnd_sleep)
	{
		wnd_sleep->setBounds(getBounds());
		wnd_sleep->setText(getText());
		wnd_sleep->setStyle(getStyle());
		wnd_sleep->setStyleEx(getStyleEx());
	}

	bool WndWake::create(const std::wstring & title, const RectF & rect)
	{
		return true;
	}

	bool WndWake::close(int ret)
	{
		::PostMessageW(m_hwnd, WM_CLOSE, 0, 0);
		return true;
	}

	void WndWake::destroy()
	{
		::DestroyWindow(m_hwnd);
	}

	std::wstring WndWake::getText()
	{
		std::wstring ret;
		
		int text_length = (int)::SendMessageW(m_hwnd, WM_GETTEXTLENGTH, 0, 0);
		ret.resize(text_length);
		::SendMessage(getHWND(), WM_GETTEXT, (WPARAM)(text_length + 1), (LPARAM)ret.c_str());

		return ret;
	}

	bool WndWake::setText(const std::wstring & text)
	{
		return true;
	}

	RectF WndWake::getBounds()
	{
		RectF ret;
		RECT rc;
		::GetWindowRect(m_hwnd, &rc);
		HWND parent_hwnd = m_wnd->getParentHWND();
		MapWindowRect(HWND_DESKTOP, parent_hwnd, &rc);
		ret.setRECT(rc);
		return ret;
	}

	bool WndWake::setBounds(const RectF & rect)
	{
		::SetWindowPos(m_hwnd, NULL, 
			util::to_i(rect.left), util::to_i(rect.top),
			util::to_i(rect.getWidth()), util::to_i(rect.getHeight()),
			SWP_NOZORDER | SWP_NOACTIVATE
			);

		return true;
	}

	DWORD WndWake::getStyle()
	{
		LONG ret = ::GetWindowLongW(m_hwnd, GWL_STYLE);
		// if (ret == 0) {
		// 	util::error(L"::GetWindowLongW", GetLastError());
		// }
		return ret;
	}

	bool WndWake::setStyle(DWORD style)
	{
		if (::SetWindowLongW(m_hwnd, GWL_STYLE, style) == 0) {
			util::error(L"::SetWindowLongW", GetLastError());
		}

		// Forcing the window to re-read the style for the frame.
		::SetWindowPos(m_hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE |
			SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);

		return true;
	}

	DWORD WndWake::getStyleEx()
	{
		LONG ret = ::GetWindowLongW(m_hwnd, GWL_EXSTYLE);
		// if (ret == 0) {
		//	util::error(L"::GetWindowLongW", GetLastError());
		// }
		return ret;
	}

	bool WndWake::setStyleEx(DWORD style_ex)
	{
		if (::SetWindowLongW(getHWND(), GWL_EXSTYLE, style_ex) == 0) {
			util::error(L"::SetWindowLongW", GetLastError());
		}

		// Forcing the window to re-read the style for the frame.
		::SetWindowPos(m_hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE |
			SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);

		return true;
	}

	static wchar_t * PROPERTY = L"INOUIPTR";

	WndWake * WndWake::getFromHWND(HWND hwnd)
	{
		if (hwnd) {
			return (WndWake*)::GetProp(hwnd, PROPERTY);
		}

		return NULL;
	}

	void WndWake::attachToHWND(HWND hwnd)
	{
		m_hwnd = hwnd;
		::SetProp(hwnd, PROPERTY, this);
	}

	void WndWake::detachFromHWND(HWND hwnd)
	{
		::RemoveProp(hwnd, PROPERTY);
		m_hwnd = NULL;
	}

	bool WndWake::handleMessage(Msg * io_msg)
	{
		switch(io_msg->getMessage())
		{
		case WM_CLOSE:
			if (m_wnd->onClose()) {
				destroy();
			}
			return true;
		case WM_DESTROY:
			m_wnd->onDestroy();
			break;
		}
		return false;
	}

	void WndWake::callDefaultWNDPROC(Msg * io_msg)
	{
		io_msg->setLRESULT(::DefWindowProc(io_msg->getHWND(), io_msg->getMessage(), io_msg->getWPARAM(), io_msg->getLPARAM()));
	}

	void WndWake::callWNDPROC(Msg * io_msg, WNDPROC wnd_proc)
	{
		io_msg->setLRESULT(::CallWindowProc(wnd_proc, io_msg->getHWND(), io_msg->getMessage(), io_msg->getWPARAM(), io_msg->getLPARAM()));
	}

	LRESULT CALLBACK WndWake::_proc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
	{
		Msg msg(hwnd, uiMsg, wParam, lParam);
		WndWake * wnd;

		// part important when creating a new window
		if (msg.getMessage() == WM_NCCREATE)
		{
			CREATESTRUCT * cs = (CREATESTRUCT*)msg.getLPARAM();
			INO_ASSERT_DEBUG(cs);
			wnd = (WndWake*)cs->lpCreateParams;
			INO_CHECK_PTR(wnd);
			if (wnd)
			{
				wnd->attachToHWND(msg.getHWND());
				wnd->callDefaultWNDPROC(&msg);
			}
		}
		else
		{
			wnd	= getFromHWND(msg.getHWND());

			// Pass the message to the WndWake
			if (wnd)
			{
				if (!wnd->handleMessage(&msg))
				{
					wnd->callDefaultWNDPROC(&msg);
				}
			}
			// WM_GETMINMAXINFO seem to be sent before WM_NCCREATE, so we ignore it here
			else if (msg.getMessage() != WM_GETMINMAXINFO)
			{
				// throw IllegalStateException(_T("Cannot find window!"));
				INO_NOT_REACHED();
			}
		}

		return msg.getLRESULT();
	}
}