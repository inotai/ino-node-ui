#include "precompiled.h"

#include "ui/util.h"

namespace ui {

	void util::error(const wchar_t * method, DWORD error)
	{
		log_error(method, error);
		// @todo Exception.
		INO_NOT_REACHED();
	}

	void util::log_error(const wchar_t * method, DWORD error)
	{
		LPVOID lpMsgBuf;

		::FormatMessageW(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			error,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &lpMsgBuf,
			0, NULL
			);

		{
			std::wcout << method << L": " << (const TCHAR *)lpMsgBuf << L" (code: " << error << L")" << std::endl;
		}

		::LocalFree(lpMsgBuf);
	}

}