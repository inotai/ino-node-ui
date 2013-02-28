#include "precompiled.h"

#include "ui/util.h"
#include "ui/Core.h"
#include "ui/Dispatcher.h"
#include "ui/Msg.h"
#include "ui/Wnd.h"

namespace ui {

	Wnd::Wnd(Core * core, const std::wstring & class_name)
	:	m_core(core),
		m_class_name(class_name),
		m_sleep(new WndSleep()),
		m_parent(NULL)
	{
		m_state = &*m_sleep;
	}

	Wnd::~Wnd()
	{
	}

	HINSTANCE Wnd::getInstance()
	{
		return m_core->getInstance();
	}

	HWND Wnd::getHWND()
	{
		if (isWake()) {
			return m_wake->getHWND();
		}
		return NULL;
	}

	void Wnd::sleep()
	{
		if (!isSleep())
		{
			m_wake->sleep(&*m_sleep);
			m_wake->destroy();
			m_state = &*m_sleep;
			notifySleep();
		}
	}

	void Wnd::wake()
	{
		if (!isWake())
		{
			if (m_wake == NULL) {
				m_wake.reset(new WndWake(this));
			}
			m_wake->wake();
			m_state = &*m_wake;
			notifyWake();
		}
	}

	void Wnd::notifySleep()
	{
		Children::iterator it = m_children.begin();
		for(; it != m_children.end(); it++) {
			(*it)->sleep();
		}
	}

	void Wnd::notifyWake()
	{
		Children::iterator it = m_children.begin();
		for(; it != m_children.end(); it++) {
			(*it)->wake();
		}
	}

	HWND Wnd::getParentHWND()
	{
		if (m_parent) {
			return m_parent->getHWND();
		}
		return NULL;
	}

	shared_ptr<Wnd> Wnd::addChild(shared_ptr<Wnd> wnd)
	{
		if (wnd->getParent() == this) {
			return wnd;
		} else if (wnd->getParent() != NULL) {
			wnd->getParent()->removeChild(wnd);
		}

		m_children.push_back(wnd);
		wnd->setParent(this);
		return wnd;
	}

	shared_ptr<Wnd> Wnd::removeChild(shared_ptr<Wnd> wnd)
	{
		Children::iterator it = std::find(m_children.begin(), m_children.end(), wnd);
		INO_ASSERT(it != m_children.end());
		if (it != m_children.end()) {
			wnd->setParent(NULL);
			m_children.erase(it);
		}
		return wnd;
	}

	void Wnd::setParent(Wnd * parent)
	{
		if (parent != NULL && parent->isWake())
		{
			sleep();
			m_parent = parent;
			wake();
		}
		else // parent == NULL || parent->isSleep()
		{
			sleep();
			// Sleep uses parent to save the coordinates
			// so we must set the parent afterwards.
			m_parent = parent;
		}
	}

	bool Wnd::onClose()
	{
		if (on_close.empty() || on_close(this) == true) {
			return true;
		}
		return false;
	}

	void Wnd::onDestroy()
	{
		if (!on_destroy.empty()) {
			on_destroy(this);
		}
		sleep();
	}
}