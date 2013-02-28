#ifndef __UV_THREAD_H__
#define __UV_THREAD_H__

namespace uv {

	class Thread
	{
	public:
		Thread()
		:	m_thread(NULL)
		{};

		virtual ~Thread()
		{};

		typedef void (*Callable)(void*);
		void start(Callable callable, void * arg)
		{
			uv_thread_create(&m_thread, callable, arg);
		}

		void join()
		{
			uv_thread_join(&m_thread);
			m_thread = NULL;
		}

	private:
		uv_thread_t m_thread;
	};

}

#endif // __UV_THREAD_H__