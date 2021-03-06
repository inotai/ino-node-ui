#include "precompiled.h"
#include "ino/Debugger.h"

#include <sstream>
#include <cstdlib>
#include <cstdio>
#if defined(INO_OS_FAMILY_UNIX) && !defined(INO_VXWORKS)
	#include <unistd.h>
	#include <signal.h>
#elif defined(INO_OS_FAMILY_VMS)
	#include <lib$routines.h>
	#include <ssdef.h>
#endif

// #if defined(POCO_WIN32_UTF8) && !defined(POCO_NO_WSTRING)
// #include "Poco/UnicodeConverter.h"
// #endif


// NOTE: In this module, we use the C library functions (fputs) for,
// output since, at the time we're called, the C++ iostream objects std::cout, etc.
// might not have been initialized yet.

namespace ino
{

	//------------------------------------------------------------------------
	bool Debugger::isAvailable()
	//------------------------------------------------------------------------
	{
	#if defined(_DEBUG)
		#if defined(INO_OS_FAMILY_WINDOWS)
			#if defined(_WIN32_WCE)
				#if (_WIN32_WCE >= 600)
					BOOL isDebuggerPresent;
					if (CheckRemoteDebuggerPresent(GetCurrentProcess(), &isDebuggerPresent))
					{
						return isDebuggerPresent ? true : false;
					}
					return false;
				#else
					return false;
				#endif
			#else
				return IsDebuggerPresent() ? true : false;
			#endif
		#elif defined(INO_VXWORKS)
			return false;
		#elif defined(INO_OS_FAMILY_UNIX)
			return std::getenv("POCO_ENABLE_DEBUGGER") ? true : false;
		#elif defined(INO_OS_FAMILY_VMS)
			return true;
		#endif
	#else
		return false;
	#endif
	}

	//------------------------------------------------------------------------
	void Debugger::message( const std::wstring& msg )
	//------------------------------------------------------------------------
	{
	#if defined(_DEBUG)
		#if defined(_UNICODE)
			std::fputws(L"\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", stderr);
			std::fputws(msg.c_str(), stderr);
			std::fputws(L"\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", stderr);
		#else
			std::fputs("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", stderr);
			std::fputs(msg.c_str(), stderr);
			std::fputs("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", stderr);
		#endif

		#if defined(INO_OS_FAMILY_WINDOWS)
		if (isAvailable())
		{
			#if defined(_UNICODE)
				std::wstring msg_cr(msg);
				msg_cr += '\n';
				OutputDebugStringW(msg_cr.c_str());
			#elif defined(POCO_WIN32_UTF8) && !defined(POCO_NO_WSTRING)
				std::wstring umsg;
				UnicodeConverter::toUTF16(msg, umsg);
				umsg += '\n';
				OutputDebugStringW(umsg.c_str());
			#else
				OutputDebugStringA(msg.c_str());
				OutputDebugStringA("\n");
			#endif
		}
		#elif defined(INO_OS_FAMILY_UNIX)
		#elif defined(INO_OS_FAMILY_VMS)
		#endif
	#endif
	}

	//------------------------------------------------------------------------
	void Debugger::message( const std::wstring& msg, const wchar_t* file, int line )
	//------------------------------------------------------------------------
	{
	#if defined(_DEBUG)
		#if defined(INO_OS_FAMILY_WINDOWS) && defined(_UNICODE)
			std::wostringstream str;
			str << msg << L"\n\t" << file << L"(" << line << ")";
			message(str.str());
		#else
			std::ostringstream str;
			str << msg << " [in file \"" << file << "\", line " << line << "]";
			message(str.str());
		#endif
	#endif
	}


	//------------------------------------------------------------------------
	void Debugger::enter()
	//------------------------------------------------------------------------
	{
	#if defined(_DEBUG)
		#if defined(INO_OS_FAMILY_WINDOWS)
		if (isAvailable())
		{
			DebugBreak();
		}
		#elif defined(INO_VXWORKS)
		{
			// not supported
		}
		#elif defined(INO_OS_FAMILY_UNIX)
		if (isAvailable())
		{
			kill(getpid(), SIGINT);
		}
		#elif defined(INO_OS_FAMILY_VMS)
		{
			const char* cmd = "\012SHOW CALLS";
			lib$signal(SS$_DEBUG, 1, cmd);
		}
		#endif
	#endif
	}

	//------------------------------------------------------------------------
	void Debugger::enter( const std::wstring& msg )
	//------------------------------------------------------------------------
	{
	#if defined(_DEBUG)
		message(msg);
		enter();
	#endif
	}


	//------------------------------------------------------------------------
	void Debugger::enter( const std::wstring& msg, const wchar_t* file, int line )
	//------------------------------------------------------------------------
	{
	#if defined(_DEBUG)
		message(msg, file, line);
		enter();
	#endif
	}


	//------------------------------------------------------------------------
	void Debugger::enter( const wchar_t* file, int line )
	//------------------------------------------------------------------------
	{
	#if defined(_DEBUG)
		message(L"BREAK", file, line);
		enter();
	#endif
	}


}
