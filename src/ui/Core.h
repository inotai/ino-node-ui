#ifndef __UI_CORE_H__
#define __UI_CORE_H__

namespace ui {

	class Factory;
	class Dispatcher;

	class Core
	{
	public:
		Core(HINSTANCE hinst);
		~Core();

		void initialize();
		void release();

		void quit();

		/// Returns HINSTANCE
		HINSTANCE getInstance()
		{ return m_hinst; }

		/// Returns factory
		Factory * getFactory()
		{ return m_factory.get(); }

		Dispatcher * getDispatcher()
		{ return m_dispatcher.get(); }

	private:
		HINSTANCE m_hinst;
		shared_ptr<Dispatcher> m_dispatcher;
		shared_ptr<Factory> m_factory;
	};

}

#endif // __UI_CORE_H__