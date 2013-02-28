#ifndef __UI_UTIL_H__
#define __UI_UTIL_H__

namespace ui {

	struct util
	{
		static inline int to_i(float f)
		{ return (int)floor(f + 0.5); }

		static void error(const wchar_t * method, DWORD error);
		static void log_error(const wchar_t * method, DWORD error);
	};

}

#endif // __UI_UTIL_H__