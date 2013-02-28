#include "precompiled.h"
#include "ino/Debugger.h"
#include "ino/BugCheck.h"

#include <sstream>

namespace ino
{
	//------------------------------------------------------------------------
	void BugCheck::assertion( const wchar_t* cond, const wchar_t* file, int line )
	//------------------------------------------------------------------------
	{
		std::wstring m = util::format(L"Assertion violation: %s", cond);
		Debugger::enter(m, file, line );

#ifndef _DEBUG
		INO_LOG(_T("Assertion violation: `%s`\n\t%s(%d)"), cond, file, line);
 		tstring w;
 		what( cond, file, line, &w );
 		throw AssertionViolationException( w.c_str() );
#endif
	}

	//------------------------------------------------------------------------
	void BugCheck::assertionLog(const wchar_t * cond, const wchar_t * file, int line)
	//------------------------------------------------------------------------
	{
#ifdef _DEBUG
		assertion(cond, file, line);
#else
		INO_LOG_ERROR(_SV(0xb1ef4fab, "assert"), _T("Assertion failed for `%s` in %s : %d."), cond, file, line);
#endif
	}

	//------------------------------------------------------------------------
	void BugCheck::nullPointer( const wchar_t* ptr, const wchar_t* file, int line )
	//------------------------------------------------------------------------
	{
		std::wstring m = util::format(L"NULL pointer: %s", ptr);
		Debugger::enter(m, file, line);

#ifndef _DEBUG
		INO_LOG(_T("NULL pointer: `%s`\n\t%s(%d)"), ptr, file, line);
		tstring w;
		what( ptr, file, line, &w );
		throw NullPointerException( w.c_str() );
#endif
	}

	//------------------------------------------------------------------------
	void BugCheck::notReached(const wchar_t * file, int line)
	//------------------------------------------------------------------------
	{
		std::wstring m = util::format(L"Not reached: %s", file);
		Debugger::enter(m, file, line);

#ifndef _DEBUG
		INO_LOG(_T("Not reached:\n\t%s(%d)"), file, line);
		throw IllegalStateException(_T("Not reached"));
#endif
	}

	//------------------------------------------------------------------------
	void BugCheck::notImplemented(const wchar_t * file, int line)
	//------------------------------------------------------------------------
	{
		Debugger::enter(L"Not implemented", file, line);

#ifndef _DEBUG
		INO_LOG(_T("NotImplemented violation:\n\t%s(%d)"), file, line);
		throw NotImplementedException(_T("Not implemented"));
#endif
	}

	//------------------------------------------------------------------------
	void BugCheck::what( const wchar_t* msg, const wchar_t* file, int line, std::wstring* o_msg )
	//------------------------------------------------------------------------
	{
#if defined(_UNICODE)
		std::wostringstream str;
		if (msg) str << msg << L" ";
		str << L"in file \"" << file << L"\", line " << line;
		*o_msg = str.str();
#else
		std::ostringstream str;
		if (msg) str << msg << " ";
		str << "in file \"" << file << "\", line " << line;
		*o_msg = str.str();
#endif
	}
}