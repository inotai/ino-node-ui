#pragma once
#ifndef __INO_DEBUGGER_H__
#define __INO_DEBUGGER_H__

namespace ino
{

	//------------------------------------------------------------------------
	/// The Debugger class provides an interface to the debugger.
	/// The presence of a debugger can be checked for,
	/// messages can be written to the debugger's log window
	/// and a break into the debugger can be enforced.
	/// The methods only work if the program is compiled
	/// in debug mode (the macro _DEBUG is defined).
	///
	/// Adopted from Poco
	//------------------------------------------------------------------------
	class Debugger
	//------------------------------------------------------------------------
	{
	public:
		/// Returns true if a debugger is available, false otherwise.
		/// On Windows, this function uses the IsDebuggerPresent()
		/// function.
		///
		/// On Unix, this function returns true if the environment
		/// variable INO_ENABLE_DEBUGGER is set.
		///
		/// On OpenVMS, this function always returns true in debug,
		/// mode, false otherwise.
		static bool isAvailable();

		/// Writes a message to the debugger log, if available, otherwise to
		/// standard error output.
		static void message( const std::wstring& msg );

		/// Writes a message to the debugger log, if available, otherwise to
		/// standard error output.
		static void message( const std::wstring& msg, const TCHAR* file, int line );

		/// Breaks into the debugger, if it is available.
		/// On Windows, this is done using the DebugBreak() function.
		/// On Unix, the SIGINT signal is raised.
		/// On OpenVMS, the SS$_DEBUG signal is raised.
		static void enter();

		/// Writes a debug message to the debugger log and breaks into it.
		static void enter( const std::wstring& msg );

		/// Writes a debug message to the debugger log and breaks into it.
		static void enter( const std::wstring& msg, const TCHAR* file, int line );

		/// Writes a debug message to the debugger log and breaks into it.
		static void enter( const TCHAR* file, int line );
	};

}

#endif // __INO_DEBUGGER_H__