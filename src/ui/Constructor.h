#ifndef __UI_CONSTRUCTOR_H__
#define __UI_CONSTRUCTOR_H__

namespace ui {

	class Wnd;
	class Dispatcher;

	struct Constructor
	{
		virtual Wnd * create(Dispatcher * dispatcher)
		{
			return NULL;
		};
	};

	template<class T>
	struct TConstructor : public Constructor
	{
		virtual Wnd * create(Dispatcher * dispatcher)
		{
			return new T(dispatcher);
		}
	};


}

#endif // __UI_CONSTRUCTOR_H__