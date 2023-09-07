#include "LuPCH.hpp"
#include "Log.hpp"

#include "spdlog/common.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace Lumina
{
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger = spdlog::stderr_color_mt("LUMINA");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stderr_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);
    }

} // namespace Lumina