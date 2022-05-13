/**
 * @file    detection.h
 * @brief   Platorm detection using predefined macros
 * @author  Thiago Rezende (thiago.manoel.rezende@gmail.com)
 *
 * This header will provide some macros to identify the platform.
 * This can be used for compile time restrictions or for platform specific code
 * sections.
 *
 * To apply platform restrictions, just uncomment the #error on the desired
 * platform
 *
 */

#ifndef HORUS_PLATFORM_DETECTION_H
#define HORUS_PLATFORM_DETECTION_H

/* Check for Emscripten */
#if defined(__EMSCRIPTEN__)
#define PLATFORM_EMSCRIPTEN
#error "[platform]: Emscripten platform is not supported!"
/* Check for Windows platform */
#elif defined(_WIN32)
#define PLATFORM_WINDOWS
#error "[platform]: Windows platform is not supported!"
/* Windows x64/x86 */
#if defined(_WIN64)
/* Windows x64  */
#define PLATFORM_WINDOWS_64
#error "[platform]: Windows x64 builds are not supported!"
#else // _WIN64
/* Windows x86 */
#define PLATFORM_WINDOWS_86
#error "[platform]: Windows x86 builds are not supported!"
#endif // _WIN32
/* Check for Apple flatofrms */
#elif defined(__APPLE__) || defined(__MACH__)
#define PLATFORM_APPLE
#error "[platform]: Apple platforms are not supported!"
#include <TargetConditionals.h>
/* TARGET_OS_MAC exists on all Apple platforms
 * so we must check all of them (in this order)
 * to ensure that we're running on MAC
 * and not some other Apple platform
 */
#if TARGET_IPHONE_SIMULATOR == 1
#define PLATFORM_IOS_SIMULATOR
#error "[platform]: IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define PLATFORM_IOS
#error "[platform]: IOS is not supported!"
#elif TARGET_OS_MAC == 1
#define PLATFORM_MACOS
#error "[platform]: MacOS is not supported!"
#else
#error "[platform]: Unknown Apple platform!"
#endif // __APPLE__ || __MACH__
/* Check for __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined
 */
#elif defined(__ANDROID__)
#define PLATFORM_ANDROID
#error "[platform]: Android is not supported!"
/* Check for linux */
#elif defined(__linux__)
#define PLATFORM_LINUX
// #error "[platform]: Linux is not supported!"
/* Check for FreeBSD */
#elif defined(__FreeBSD__)
#define PLATFORM_FREEBSD
#error "[platform]: FreeBSD is not supported!"
#else // __FreeBSD__
/* Unknown compiler/platform */
#error "[platform]: Unknown platform!"
#endif

#endif // !HORUS_PLATFORM_DETECTION_H
