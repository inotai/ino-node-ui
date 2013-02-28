#include "precompiled.h"

#include "uv/Semaphore.h"

#include "ui/util.h"
#include "ui/Factory.h"
#include "ui/Message.h"

#include "ui/Dispatcher.h"

namespace ui {

	Dispatcher::Dispatcher()
	:	m_ui_thread_id(0)
	{
		m_queue_message = ::RegisterWindowMessageW(L"NodeUI.Dispatcher.QueueMessage");
	}

	Dispatcher::~Dispatcher()
	{
	}

	void Dispatcher::init()
	{
		m_uv_async.init(uv_default_loop(), &Dispatcher::onAsync);
		m_uv_async.setData(this);

		m_ui_thread.start(&Dispatcher::_run, this);
		m_ui_thread_start_semaphore.wait();
	}

	void Dispatcher::quit()
	{
		::PostThreadMessageW(m_ui_thread_id, WM_QUIT, 0, 0);
	}

	void Dispatcher::send(shared_ptr<Message> message)
	{
		message->m_sem = &m_ui_sem;
		queue(message);
		m_ui_sem.wait();
	}

	void Dispatcher::_send(shared_ptr<Message> message)
	{
		message->m_sem = &m_uv_sem;
		m_uv_queue.push(message);
		m_uv_async.signal();
		m_uv_sem.wait();
	}

	void Dispatcher::queue(shared_ptr<Message> message)
	{
		m_ui_queue.push(message);

		if (::PostThreadMessage(m_ui_thread_id, m_queue_message, 0, 0) == 0) {
			util::log_error(L"::PostThreadMessage", ::GetLastError());
		}
	}

	void Dispatcher::_run(void * arg)
	{
		Dispatcher * dispatcher = reinterpret_cast<Dispatcher*>(arg);
		dispatcher->_run();
	}

	void Dispatcher::_run()
	{
		m_ui_thread_id = ::GetCurrentThreadId();
		m_ui_thread_start_semaphore.signal();
	
		MSG msg;
		while (1)
		{
			if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			
				if (msg.message == WM_QUIT)
				{
					break;
				}
				else if (msg.message == m_queue_message)
				{
					shared_ptr<Message> message;
					if (m_ui_queue.pop(&message))
					{
						message->dispatch();
					}
				}
			}
			else
			{
				::WaitMessage();
			}
		}
	}

	void Dispatcher::onAsync(uv::Async * async)
	{
		Dispatcher * dispatcher = (Dispatcher*)async->getData();
		shared_ptr<Message> message;
		if (dispatcher->m_uv_queue.pop(&message))
		{
			message->dispatch();
		}
	}
}