#pragma once

#include "Core.hpp"

#include "spdlog/logger.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <memory>

namespace Lumina
{


class LUMINA_API Log
{
public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
    {
        return s_CoreLogger;
    }
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
    {
        return s_ClientLogger;
    }

private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};
} // namespace Lumina

// Core log
#define LU_CORE_TRACE(...) ::Lumina::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LU_CORE_INFO(...) ::Lumina::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LU_CORE_WARN(...) ::Lumina::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LU_CORE_ERROR(...) ::Lumina::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LU_CORE_FATAL(...) ::Lumina::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// App log
#define LU_TRACE(...) ::Lumina::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LU_INFO(...) ::Lumina::Log::GetClientLogger()->info(__VA_ARGS__)
#define LU_WARN(...) ::Lumina::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LU_ERROR(...) ::Lumina::Log::GetClientLogger()->error(__VA_ARGS__)
#define LU_FATAL(...) ::Lumina::Log::GetClientLogger()->fatal(__VA_ARGS__)
