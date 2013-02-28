#pragma once
#ifndef __INO_BUG_CHECK_H__
#define __INO_BUG_CHECK_H__

namespace ino
{
	//------------------------------------------------------------------------
	/// A set of check methods for catching bugs.
	class BugCheck
	//------------------------------------------------------------------------
	{
	public:

		/// An assertion failed. Break into the debugger, if
		/// possible, then throw an AssertionViolationException.
		static void assertion(const wchar_t * cond, const wchar_t * file, int line);

		/// An assertion failed. 
		/// - DEBUG: Calls assertion()
		/// - RELEASE: Just logs the error.
		static void assertionLog(const wchar_t * cond, const wchar_t * file, int line);

		/// An null pointer was encountered. Break into the debugger, if
		/// possible, then throw an NullPointerException.
		static void nullPointer(const wchar_t * ptr, const wchar_t * file, int line);

		static void notReached(const wchar_t * file, int line);
		static void notImplemented(const wchar_t * file, int line);


		/// Checks if given pointer is NULL
		template<typename T>
		static void checkNullPointer(T * ptr, const wchar_t * ptr_str, const wchar_t * file, int line)
		{
			if (ptr == NULL) {
				nullPointer(ptr_str, file, line);
			}
		}

		/// Checks if given shared_ptr is NULL
		template<typename T>
		static void checkNullPointer(shared_ptr<T> ptr, const wchar_t * ptr_str, const wchar_t * file, int line)
		{
			checkNullPointer(ptr.get(), ptr_str, file, line);
		}

	private:
		static void what(const wchar_t* msg, const wchar_t* file, int line, std::wstring* o_msg);
	};

#ifdef _UNICODE

	/// DEBUG: Breaks into the debugger.
	/// RELEASE: Throws AssertionException
	#define INO_ASSERT(cond) \
	if(!(cond)) ino::BugCheck::assertion(L#cond, INO_WFILE, __LINE__); else (void) 0

	/// DEBUG: Breaks into the debugger.
	/// RELEASE: Logs the error. (no breaks or exceptions are thrown)
	#define INO_ASSERT_LOG(cond) \
	if(!(cond)) ::ino::BugCheck::assertionLog(_T(#cond), INO_WFILE, __LINE__); else (void) 0

	/// DEBUG: Breaks into the debugger
	/// RELEASE: throws IllegalStateException
	#define INO_NOT_REACHED() \
	::ino::BugCheck::notReached(INO_WFILE, __LINE__)

	/// DEBUG: Breaks into the debugger
	/// RELEASE: throws NotImplementedException
	#define INO_NOT_IMPLEMENTED() \
	::ino::BugCheck::notImplemented(INO_WFILE, __LINE__)

	/// DEBUG: Breaks into the debugger.
	/// RELEASE: throws NullPointerException if ptr == NULL
	/// Also works with shared_ptr
	#define INO_CHECK_PTR(ptr) \
	::ino::BugCheck::checkNullPointer(ptr, L#ptr, INO_WFILE, __LINE__)

	#define INO_CHECK_REF(r) \
	if((&(r)) == NULL) ::ino::BugCheck::nullPointer(L#r, INO_WFILE, __LINE__); else (void) 0

#else // ANSI

	#define INO_ASSERT(cond) \
	if(!(cond)) ::ino::BugCheck::assertion(#cond, __FILE__, __LINE__); else (void) 0

#endif 

#ifdef _DEBUG
	#define INO_ASSERT_DEBUG INO_ASSERT
#else
	#define INO_ASSERT_DEBUG INO_ASSERT_LOG
#endif
}


#endif // __INO_BUG_CHECK_H__