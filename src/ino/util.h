#ifndef __INO_UTIL_H__
#define __INO_UTIL_H__

namespace ino {

	struct util
	{
		static std::wstring format(const wchar_t* fmt, ...)
		{
			int size = 80;
			std::wstring ret;
			ret.resize(size);
			va_list vl;
			va_start(vl, fmt);
			int size_n = _vsnwprintf(&ret[0], size, fmt, vl);
			if (size <= size_n)
			{
				ret.resize(size_n + 1);
				size_n = _vsnwprintf(&ret[0], size_n, fmt, vl);
			}
			va_end(vl);
			return ret;
		}
	};

}

#endif // __INO_UTIL_H__