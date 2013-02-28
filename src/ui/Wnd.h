#ifndef __UI_WND_H__
#define __UI_WND_H__

#include "ui/IWnd.h"
#include "ui/WndWake.h"
#include "ui/WndSleep.h"
#include "ui/Message.h"

namespace ui {

	class Core;
	class Msg;
	class WndWake;
	class WndSleep;

	class Wnd : public IWnd
	{
		friend class WndWake;
	public:
		Wnd(Core * core, const std::wstring & class_name);
		virtual ~Wnd();

		Core * getCore()
		{ return m_core; }
		HINSTANCE getInstance();

		virtual const std::wstring & getClassName()
		{ return m_class_name; }
		virtual void initClass(WNDCLASSEX * ec)
		{ INO_NOT_REACHED(); }

		HWND getHWND();

		bool isWake() const
		{ return m_state == m_wake.get(); }
		bool isSleep() const
		{ return m_state == m_sleep.get(); }

		WndSleep * getSleep()
		{ return m_sleep.get(); }
		WndWake * getWake()
		{ return m_wake.get(); }

		virtual std::wstring getText()
		{ return m_state->getText(); }
		virtual bool setText(const std::wstring & text)
		{ return m_state->setText(text); }

		virtual RectF getBounds()
		{ return m_state->getBounds(); }
		virtual bool setBounds(const RectF & bounds)
		{ return m_state->setBounds(bounds); }

		virtual DWORD getStyle()
		{ return m_state->getStyle(); }
		virtual bool setStyle(DWORD style)
		{ return m_state->setStyle(style); }

		virtual DWORD getStyleEx()
		{ return m_state->getStyleEx(); }
		virtual bool setStyleEx(DWORD style_ex)
		{ return m_state->setStyleEx(style_ex); }

		virtual bool close(int ret)
		{
			if (isWake()) {
				return m_wake->close(ret);
			}
			return false;
		}


		void sleep();
		void wake();

	private:
		Core * m_core;
		std::wstring m_class_name;
		IWnd * m_state;
		shared_ptr<WndWake> m_wake;
		shared_ptr<WndSleep> m_sleep;

		void notifySleep();
		void notifyWake();

	//
	// Delegates
	//
	public:
		typedef ino::delegate1<Wnd *, bool> OnClose;
		OnClose on_close;
		typedef ino::delegate1<Wnd *> OnDestroy;
		OnDestroy on_destroy;

	//
	// Callbacks
	//
	public:
		/// Called from WndWake when window is being closed.
		/// Returns true when close can destroy the window.
		bool onClose();

		/// Called from WndWake when window is being destroyed.
		void onDestroy();


	//
	// Structure
	//
	public:
		virtual Wnd * getParent()
		{ return m_parent; }
		HWND getParentHWND();

		shared_ptr<Wnd> addChild(shared_ptr<Wnd> wnd);
		shared_ptr<Wnd> removeChild(shared_ptr<Wnd> wnd);
	private:
		Wnd * m_parent;
		typedef std::vector<shared_ptr<Wnd>> Children;
		Children m_children;

		void setParent(Wnd * wnd);

	//
	// Calls
	//
	public:
		bool addChild_(shared_ptr<Wnd> wnd)
		{ addChild(wnd); return true; };
		bool wake_(bool _)
		{ wake(); return true; }
		bool sleep_(bool _)
		{ sleep(); return true; }
	};
	
	namespace traits {
		typedef TByVal<Wnd*> WndPtr;
		typedef TByVal<shared_ptr<Wnd>> WndSharedPtr;
	}
}

#endif // __UI_WND_H__