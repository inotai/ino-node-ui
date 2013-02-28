#ifndef __UV_SCOPED_LOCK_H__
#define __UV_SCOPED_LOCK_H__

namespace uv {
	
	template<class MutexType>
	class TScopedLock
	{
	public:
		TScopedLock(MutexType & mutex)
		:	m_mutex(mutex)
		{
			m_mutex.lock();
		}
		
		~TScopedLock()
		{
			m_mutex.unlock();
		}
		
	private:
		MutexType & m_mutex;
	};
	
}

#endif // __UV_SCOPED_LOCK_H__