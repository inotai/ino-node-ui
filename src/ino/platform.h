#pragma once
#ifndef __INO_PLATFORM_H__
#define __INO_PLATFORM_H__

/// Platform and hardware identification
/// Adopted from Poco

namespace ino
{
	/// Platform identification

	#define INO_OS_FREE_BSD      0x0001
	#define INO_OS_AIX           0x0002
	#define INO_OS_HPUX          0x0003
	#define INO_OS_TRU64         0x0004
	#define INO_OS_LINUX         0x0005
	#define INO_OS_MAC_OS_X      0x0006
	#define INO_OS_NET_BSD       0x0007
	#define INO_OS_OPEN_BSD      0x0008
	#define INO_OS_IRIX          0x0009
	#define INO_OS_SOLARIS       0x000a
	#define INO_OS_QNX           0x000b
	#define INO_OS_VXWORKS       0x000c
	#define INO_OS_CYGWIN        0x000d
	#define INO_OS_UNKNOWN_UNIX  0x00ff
	#define INO_OS_WINDOWS_NT    0x1001
	#define INO_OS_WINDOWS_CE    0x1011
	#define INO_OS_VMS           0x2001

	#if defined(__FreeBSD__)
		#define INO_OS_FAMILY_UNIX 1
		#define INO_OS_FAMILY_BSD 1
		#define INO_OS INO_OS_FREE_BSD
	#elif defined(_AIX) || defined(__TOS_AIX__)
		#define INO_OS_FAMILY_UNIX 1
		#define INO_OS INO_OS_AIX
	#elif defined(hpux) || defined(_hpux)
		#define INO_OS_FAMILY_UNIX 1
		#define INO_OS INO_OS_HPUX
	#elif defined(__digital__) || defined(__osf__)
		#define INO_OS_FAMILY_UNIX 1
		#define INO_OS INO_OS_TRU64
	#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__TOS_LINUX__)
		#define INO_OS_FAMILY_UNIX 1
		#define INO_OS INO_OS_LINUX
	#elif defined(__APPLE__) || defined(__TOS_MACOS__)
		#define INO_OS_FAMILY_UNIX 1
		#define INO_OS_FAMILY_BSD 1
		#define INO_OS INO_OS_MAC_OS_X
	#elif defined(__NetBSD__)
		#define INO_OS_FAMILY_UNIX 1
		#define INO_OS_FAMILY_BSD 1
		#define INO_OS INO_OS_NET_BSD
	#elif defined(__OpenBSD__)
		#define INO_OS_FAMILY_UNIX 1
		#define INO_OS_FAMILY_BSD 1
		#define INO_OS INO_OS_OPEN_BSD
	#elif defined(sgi) || defined(__sgi)
		#define INO_OS_FAMILY_UNIX 1
		#define INO_OS INO_OS_IRIX
	#elif defined(sun) || defined(__sun)
		#define INO_OS_FAMILY_UNIX 1
		#define INO_OS INO_OS_SOLARIS
	#elif defined(__QNX__)
		#define INO_OS_FAMILY_UNIX 1
		#define INO_OS INO_OS_QNX
	#elif defined(unix) || defined(__unix) || defined(__unix__)
		#define INO_OS_FAMILY_UNIX 1
		#define INO_OS INO_OS_UNKNOWN_UNIX
	#elif defined(_WIN32_WCE)
		#define INO_OS_FAMILY_WINDOWS 1
		#define INO_OS INO_OS_WINDOWS_CE
	#elif defined(_WIN32) || defined(_WIN64)
		#define INO_OS_FAMILY_WINDOWS 1
		#define INO_OS INO_OS_WINDOWS_NT
		/// Additional switch (currently used by the library, will have to be solved)
		/// ToDo: Get rid of this
	#elif defined(__CYGWIN__)
		#define INO_OS_FAMILY_UNIX 1
		#define INO_OS INO_OS_CYGWIN
	#elif defined(__VMS)
		#define INO_OS_FAMILY_VMS 1
		#define INO_OS INO_OS_VMS
	#elif defined(INO_VXWORKS)
	  #define INO_OS_FAMILY_UNIX 1
	  #define INO_OS INO_OS_VXWORKS
	#endif

	/// Hardware Architecture and Byte Order

	#define INO_ARCH_ALPHA   0x01
	#define INO_ARCH_IA32    0x02
	#define INO_ARCH_IA64    0x03
	#define INO_ARCH_MIPS    0x04
	#define INO_ARCH_HPPA    0x05
	#define INO_ARCH_PPC     0x06
	#define INO_ARCH_POWER   0x07
	#define INO_ARCH_SPARC   0x08
	#define INO_ARCH_AMD64   0x09
	#define INO_ARCH_ARM     0x0a
	#define INO_ARCH_M68K    0x0b
	#define INO_ARCH_S390    0x0c
	#define INO_ARCH_SH      0x0d


	#if defined(__ALPHA) || defined(__alpha) || defined(__alpha__) || defined(_M_ALPHA)
		#define INO_ARCH INO_ARCH_ALPHA
		#define INO_ARCH_LITTLE_ENDIAN 1
	#elif defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_IX86)
		#define INO_ARCH INO_ARCH_IA32
		#define INO_ARCH_LITTLE_ENDIAN 1
	#elif defined(_IA64) || defined(__IA64__) || defined(__ia64__) || defined(__ia64) || defined(_M_IA64)
		#define INO_ARCH INO_ARCH_IA64
		#if defined(hpux) || defined(_hpux)
			#define INO_ARCH_BIG_ENDIAN 1
		#else
			#define INO_ARCH_LITTLE_ENDIAN 1
		#endif
	#elif defined(__x86_64__) || defined(_M_X64)
		#define INO_ARCH INO_ARCH_AMD64
		#define INO_ARCH_LITTLE_ENDIAN 1
	#elif defined(__mips__) || defined(__mips) || defined(__MIPS__) || defined(_M_MRX000)
		#define INO_ARCH INO_ARCH_MIPS
		#define INO_ARCH_BIG_ENDIAN 1
	#elif defined(__hppa) || defined(__hppa__)
		#define INO_ARCH INO_ARCH_HPPA
		#define INO_ARCH_BIG_ENDIAN 1
	#elif defined(__PPC) || defined(__POWERPC__) || defined(__powerpc) || defined(__PPC__) || \
		  defined(__powerpc__) || defined(__ppc__) || defined(__ppc) || defined(_ARCH_PPC) || defined(_M_PPC)
		#define INO_ARCH INO_ARCH_PPC
		#define INO_ARCH_BIG_ENDIAN 1
	#elif defined(_POWER) || defined(_ARCH_PWR) || defined(_ARCH_PWR2) || defined(_ARCH_PWR3) || \
		  defined(_ARCH_PWR4) || defined(__THW_RS6000)
		#define INO_ARCH INO_ARCH_POWER
		#define INO_ARCH_BIG_ENDIAN 1
	#elif defined(__sparc__) || defined(__sparc) || defined(sparc)
		#define INO_ARCH INO_ARCH_SPARC
		#define INO_ARCH_BIG_ENDIAN 1
	#elif defined(__arm__) || defined(__arm) || defined(ARM) || defined(_ARM_) || defined(__ARM__) || defined(_M_ARM)
		#define INO_ARCH INO_ARCH_ARM
		#if defined(__ARMEB__)
			#define INO_ARCH_BIG_ENDIAN 1
		#else
			#define INO_ARCH_LITTLE_ENDIAN 1
		#endif
	#elif defined(__m68k__)
		#define INO_ARCH INO_ARCH_M68K
		#define INO_ARCH_BIG_ENDIAN 1
	#elif defined(__s390__)
		#define INO_ARCH INO_ARCH_S390
		#define INO_ARCH_BIG_ENDIAN 1
	#elif defined(__sh__) || defined(__sh)
		#define INO_ARCH INO_ARCH_SH
		#if defined(__LITTLE_ENDIAN__)
			#define INO_ARCH_LITTLE_ENDIAN 1
		#else
			#define INO_ARCH_BIG_ENDIAN 1
		#endif
	#endif
}

#endif // __INO_PLATFORM_H__