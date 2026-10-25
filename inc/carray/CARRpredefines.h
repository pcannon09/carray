/**
 * CARRpredefines.h - pcannonProjectStandards
 * Predefines for C and C++ projects
 * STD Information: 20250723 - 1.0S
 */

#pragma once

// Versioning
#define CARR_VERSION_MAJOR			  1
#define CARR_VERSION_MINOR			  0
#define CARR_VERSION_PATCH			  0

#define CARR_VERSION_STD				20261025

// Version states:
// * dev
// * beta
// * build
#define CARR_VERSION_STATE		  "build"

#define CARR_VERSION				((CARR_VERSION_MAJOR<<16)|(CARR_VERSION_MINOR<<8)|(CARR_VERSION_PATCH)|(CARR_VERSION_STATE << 24))

#define CARR_VERSION_CHECK(CARR_VERSION_MAJOR, CARR_VERSION_MINOR, CARR_VERSION_PATCH, CARR_VERSION_STATE) \
	(((CARR_VERSION_MAJOR)<<16)|((CARR_VERSION_MINOR)<<8)|(CARR_VERSION_PATCH)|((CARR_VERSION_STATE) << 24))

// Macro utils
#define CARR_STRINGIFY(x) #x
#define CARR_TOSTRING(x) CARR_STRINGIFY(x)

#ifndef CARR_DEV
#   define CARR_DEV true
#endif

#define CARR_FREE(_x) \
	do { \
		free(_x); \
		_x = NULL; \
	} while (0)

#if defined(WIN32) || defined(_WIN32)
#	define CARR_OS_WIN32
#elif defined(__APPLE__) || defined(__MACH__) || defined(Macintosh)
#	define CARR_OS_MACOS
#elif defined(__linux__) || defined(__unix) || defined(__unix__)
#	define CARR_OS_UNIX_LINUX
#elif defined(__FreeBSD__)
#	define CARR_OS_FREEBSD
#else
# 	define CARR_OS_UNKNOWN
#	warning "Current platform might not be supported"
#endif // defined(WIN32) // Platform check

