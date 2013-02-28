#ifndef __UV_MUTEX_H__
#define __UV_MUTEX_H__

#include "uv/TScopedLock.h"

namespace uv {

	class Mutex
	{
	public:
		typedef TScopedLock<Mutex> ScopedLock;

		Mutex()
		{
			uv_mutex_init(&m_mutex);
		}

		virtual ~Mutex()
		{
			uv_mutex_destroy(&m_mutex);
		}

		void lock()
		{
			uv_mutex_lock(&m_mutex);
		}

		int tryLock()
		{
			return uv_mutex_trylock(&m_mutex);
		}

		void unlock()
		{
			uv_mutex_unlock(&m_mutex);
		}

	private:
		uv_mutex_t m_mutex;
	};

}

#endif // __UV_MUTEX_H__