#pragma once

#ifdef LU_PLATFORM_WINDOWS
#ifdef LU_BUILD_SHARED

#define LUMINA_API __declspec(dllexport)
#else
#define LUMINA_API __declspec(dllimport)
#endif

#endif

#ifdef LU_PLATFORM_LINUX
#ifdef LU_BUILD_SHARED

#define LUMINA_API
#else
#define LUMINA_API
#endif

#endif

#ifdef LU_PLATFORM_MAC
#error "Lumina only supports Windows and Linux"
#endif

#define BIT(x) (1 << x)
