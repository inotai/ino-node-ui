#ifndef __INO_MACROS_H__
#define __INO_MACROS_H__

// Helpers

#define INO_WIDEN2(x) L ## x
#define INO_WIDEN(x) INO_WIDEN2(x)
#define INO_WFILE INO_WIDEN(__FILE__)
#define INO_STRINGIFY(x) #x
#define INO_TOSTRING(x)  INO_STRINGIFY(x)
#define INO_TOWSTRING(x) INO_WIDEN(INO_TOSTRING(x))

// API

#ifdef INO_DLL
#define INO_API __declspec(dllexport)
#else
#define INO_API
#endif

#define INO_DEPRECATED_API __declspec(deprecated)

#endif // __INO_MACROS_H__