#ifndef __UV_QUEUE_H__
#define __UV_QUEUE_H__

#include "uv/Mutex.h"
#include <deque>

namespace uv {
	
	template<class T>
	class TQueue
	{
	public:
		TQueue()
		{
		}
		
		~TQueue()
		{
		}
		
		/// Pushes data to the queue.
		/// Takes ownership of the data.
		void push(T & data)
		{
			Mutex::ScopedLock lock(m_mutex);
			m_queue_message.push_back(data);
		}

		/// Pops data from the queue
		/// Caller takes ownership of the data.
		bool pop(T * o_data)
		{
			Mutex::ScopedLock lock(m_mutex);
			if (!m_queue_message.empty())
			{
				*o_data = m_queue_message.front();
				m_queue_message.pop_front();
				return true;
			}
			return false;
		}

	private:
		/// Data queue
		std::deque<T> m_queue_message;

		Mutex m_mutex;
	};
	
}

#endif // __UV_QUEUE_H__