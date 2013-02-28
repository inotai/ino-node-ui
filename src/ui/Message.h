#ifndef __UI_MESSAGE_H__
#define __UI_MESSAGE_H__

#include "uv/Semaphore.h"

namespace ui {
	

	class Message
	{
	public:
		Message()
		:	m_sem(NULL)
		{};

		virtual ~Message()
		{};

		virtual void dispatch()
		{
			if (m_sem) {
				m_sem->signal();
			}
		};

	private:
		friend class Dispatcher;
		uv::Semaphore * m_sem;
	};

	template<class ParamTraitsT, class RetTraitsT>
	class TMessage : public Message
	{
	public:
		typedef ino::delegate1<typename ParamTraitsT::PassType, typename RetTraitsT::PassType> Delegate;

		TMessage(Delegate d, typename ParamTraitsT::PassType p)
		:	m_delegate(d),
			m_param(p)
		{}
		
		virtual ~TMessage()
		{}
		
		virtual void dispatch()
		{
			m_ret = m_delegate(m_param);
			Message::dispatch();
		}

		typename ParamTraitsT::PassType getParam()
		{ return m_param; }
		typename RetTraitsT::PassType getRet()
		{ return m_ret; }
		
	private:
		Delegate m_delegate;
		typename ParamTraitsT::StorageType m_param;
		typename RetTraitsT::StorageType m_ret;
	};
	
}

#endif // __UI_MESSAGE_H__