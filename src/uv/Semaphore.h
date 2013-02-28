#ifndef __UV_SEMAPHORE_H__
#define __UV_SEMAPHORE_H__

namespace uv {
	
	class Semaphore
	{
	public:
		Semaphore(int value = 0)
		{
			uv_sem_init(&m_sem, value);
		}
		
		~Semaphore()
		{
			uv_sem_destroy(&m_sem);
		}
		
		void wait()
		{
			uv_sem_wait(&m_sem);
		}
		
		void signal()
		{
			uv_sem_post(&m_sem);
		}
	private:
		uv_sem_t m_sem;
	};
	
}

#endif // __UV_SEMAPHORE_H__