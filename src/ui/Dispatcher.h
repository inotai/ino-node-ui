#ifndef __UI_Dispatcher_H__
#define __UI_Dispatcher_H__

#include "uv/Thread.h"
#include "uv/Async.h"
#include "uv/Semaphore.h"
#include "uv/TQueue.h"

#include "ui/Message.h"

namespace ui {

	class Factory;
	class Message;
	
	class Dispatcher
	{
	public:
		Dispatcher();
		virtual ~Dispatcher();
		
		void init();

		void quit();

		/// Sends request to the message loop.
		void send(shared_ptr<Message> message);

		template<class ParamTraitsT, class RetTraitsT>
		typename RetTraitsT::PassType send(typename ParamTraitsT::PassType p, typename TMessage<ParamTraitsT, RetTraitsT>::Delegate d)
		{
			typedef TMessage<ParamTraitsT, RetTraitsT> Msg;
			shared_ptr<Msg> msg(new Msg(d, p));
			send(msg);
			return msg->getRet();
		}
		
		/// Sends request to main thread.
		void _send(shared_ptr<Message> message);

		template<class ParamTraitsT, class RetTraitsT>
		typename RetTraitsT::PassType _send(typename ParamTraitsT::PassType p, typename TMessage<ParamTraitsT, RetTraitsT>::Delegate d)
		{
			typedef TMessage<ParamTraitsT, RetTraitsT> Msg;
			shared_ptr<Msg> msg(new Msg(d, p));
			_send(msg);
			return msg->getRet();
		}
		
	private:
		uv::Thread m_ui_thread;
		DWORD m_ui_thread_id;
		uv::Semaphore m_ui_thread_start_semaphore;
		uv::Semaphore m_ui_sem;
		uv::Semaphore m_uv_sem;
		uv::Async m_uv_async;

		UINT m_queue_message;
		typedef uv::TQueue<shared_ptr<Message>> Queue;
		Queue m_ui_queue;
		Queue m_uv_queue;
		
		void queue(shared_ptr<Message> message);
		
		static void onAsync(uv::Async * async);
		static void _run(void * arg);
		void _run();
	};
	
}

#endif // __UI_Dispatcher_H__