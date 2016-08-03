#ifndef _CORE_H
#define _CORE_H

#if defined(_WIN32)

#ifdef Core_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif

#elif defined(__linux)

#define CORE_API __attribute__ ((visibility("default")))

#endif


#endif
