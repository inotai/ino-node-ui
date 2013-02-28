#ifndef __UV_ASYNC_H__
#define __UV_ASYNC_H__

namespace uv {

	class Async;

	class Async
	{
	public:
	typedef void (*Callback)(Async *);

	private:
		struct uv_async_ex
		{
			uv_async_t async;
			void * callback;
			Async * ptr;
		};

	public:
		Async()
		{
		}

		Async(uv_loop_t * loop, Callback callback)
		{
			init(loop, callback);
		}

		~Async()
		{
			uv_close((uv_handle_t*)&m_async, NULL);
		}

		void init(uv_loop_t * loop, Callback callback)
		{
			uv_async_init(loop, (uv_async_t*)&m_async, &Async::on);
			m_async.ptr = this;
			m_async.callback = callback;
		}

		void setData(void * data)
		{ m_async.async.data = data; }
		void * getData()
		{ return m_async.async.data; }

		void signal()
		{
			uv_async_send((uv_async_t*)&m_async);
		}
	private:
		uv_async_ex m_async;

		static void on(uv_async_t * handle, int status)
		{
			uv_async_ex * ex = (uv_async_ex*)(handle);
			Callback c = (Callback)ex->callback;
			(*c)(ex->ptr);
		}
	};

}

#endif // __UV_ASYNC_H__