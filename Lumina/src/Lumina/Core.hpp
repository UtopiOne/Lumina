#pragma once


#ifdef LU_PLATFORM_WINDOWS
    #ifdef LU_BUILD_SHARED

        #define LUMINA_API __declspec(dllexport)
    #else
        #define LUMINA_API __declspec(dllimport)

    #endif

    #ifdef LU_ENABLE_ASSERTS
        #define LU_ASSERT(x, ...)                                                                                      \
            {                                                                                                          \
                if (!(x)) {                                                                                            \
                    LU_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                                    \
                    __debugbreak();                                                                                    \
                }                                                                                                      \
            }
        #define HZ_CORE_ASSERT(x, ...)                                                                                 \
            {                                                                                                          \
                if (!(x)) {                                                                                            \
                    LU_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                               \
                    __debugbreak();                                                                                    \
                }                                                                                                      \
            }
    #else
        #define LU_ASSERT(x, ...)
        #define LU_CORE_ASSERT(x, ...)
    #endif

#endif

#ifdef LU_PLATFORM_LINUX
    #include <signal.h>
    #ifdef LU_BUILD_SHARED

        #define LUMINA_API
    #else
        #define LUMINA_API
    #endif

    #ifdef LU_ENABLE_ASSERTS
        #define LU_ASSERT(x, ...)                                                                                      \
            {                                                                                                          \
                if (!(x)) {                                                                                            \
                    LU_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                                    \
                    raise(SIGTRAP);                                                                                    \
                }                                                                                                      \
            }
        #define LU_CORE_ASSERT(x, ...)                                                                                 \
            {                                                                                                          \
                if (!(x)) {                                                                                            \
                    LU_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                               \
                    raise(SIGTRAP);                                                                                    \
                }                                                                                                      \
            }
    #else
        #define LU_ASSERT(x, ...)
        #define LU_CORE_ASSERT(x, ...)
    #endif

#endif

#ifdef LU_PLATFORM_MAC
    #error "Lumina only supports Windows and Linux"
#endif


#define BIT(x) (1 << x)

#define LU_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
