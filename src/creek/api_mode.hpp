// Modification of the SDL include file begin_code.h
#pragma once

#ifndef CREEK_DEPRECATED
#  if (__GNUC__ >= 4)  /* technically, this arrived in gcc 3.1, but oh well. */
#    define CREEK_DEPRECATED __attribute__((deprecated))
#  else
#    define CREEK_DEPRECATED
#  endif
#endif

#ifndef CREEK_UNUSED
#  ifdef __GNUC__
#    define CREEK_UNUSED __attribute__((unused))
#  else
#    define CREEK_UNUSED
#  endif
#endif

/* Some compilers use a special export keyword */
#ifndef CREEK_EXPORT
# if defined(__WIN32__) || defined(__WINRT__)
#  ifdef __BORLANDC__
#   define CREEK_EXPORT
#  else
#   define CREEK_EXPORT __declspec(dllexport)
#  endif
# else
#  if defined(__GNUC__) && __GNUC__ >= 4
#   define CREEK_EXPORT __attribute__ ((visibility("default")))
#  else
#   define CREEK_EXPORT
#  endif
# endif
#endif

#ifndef CREEK_IMPORT
# if defined(__WIN32__) || defined(__WINRT__)
#  ifdef __BORLANDC__
#   define CREEK_IMPORT __declspec(dllimport)
#  else
#   define CREEK_IMPORT __declspec(dllexport)
#  endif
# else
#  if defined(__GNUC__) && __GNUC__ >= 4
#   define CREEK_IMPORT __attribute__ ((visibility("default")))
#  else
#   define CREEK_IMPORT
#  endif
# endif
#endif

#ifndef CREEK_API
# ifdef CREEK_BUILDING
#  define CREEK_API CREEK_EXPORT
# else
#  define CREEK_API CREEK_IMPORT
# endif
#endif

/* Removed CREEK_API on Symbian OS because SDL cannot be a DLL in EPOC */
#ifdef __SYMBIAN32__
#undef CREEK_API
#define CREEK_API
#endif /* __SYMBIAN32__ */

#ifndef CREEK_INLINE
#if defined(__GNUC__)
#define CREEK_INLINE __inline__
#elif defined(_MSC_VER) || defined(__BORLANDC__) || \
      defined(__DMC__) || defined(__SC__) || \
      defined(__WATCOMC__) || defined(__LCC__) || \
      defined(__DECC)
#define CREEK_INLINE __inline
#ifndef __inline__
#define __inline__ __inline
#endif
#else
#define CREEK_INLINE inline
#ifndef __inline__
#define __inline__ inline
#endif
#endif
#endif /* CREEK_INLINE not defined */

#ifndef CREEK_FORCE_INLINE
#if defined(_MSC_VER)
#define CREEK_FORCE_INLINE __forceinline
#elif ( (defined(__GNUC__) && (__GNUC__ >= 4)) || defined(__clang__) )
#define CREEK_FORCE_INLINE __attribute__((always_inline)) static __inline__
#else
#define CREEK_FORCE_INLINE static CREEK_INLINE
#endif
#endif /* CREEK_FORCE_INLINE not defined */

// Check if building for windows.
#ifndef CREEK_WINDOWS
# if defined(WIN32) || defined(_WIN32) || defined(__CYGWIN__) || defined(__MINGW32__)
#  define CREEK_WINDOWS  1
# endif
#endif
