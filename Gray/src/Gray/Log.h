#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Gray
{
	class Log
	{
	public:
		static void Init();
		static std::shared_ptr<spdlog::logger>& GetClientLogger();
		static std::shared_ptr<spdlog::logger>& GetCoreLogger();

	private:
		static std::shared_ptr<spdlog::logger> clientLogger;
		static std::shared_ptr<spdlog::logger> coreLogger;
	};
}

//Core Logger
#ifdef GRAY_DEBUG

#define GRAY_CORE_TRACE(...) Gray::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GRAY_CORE_INFO(...)  Gray::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GRAY_CORE_WARN(...)  Gray::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GRAY_CORE_ERROR(...) Gray::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GRAY_CORE_FATAL(...) Gray::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client Logger
#define GRAY_TRACE(...) Gray::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GRAY_INFO(...)  Gray::Log::GetClientLogger()->info(__VA_ARGS__)
#define GRAY_WARN(...)  Gray::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GRAY_ERROR(...) Gray::Log::GetClientLogger()->error(__VA_ARGS__)
#define GRAY_FATAL(...) Gray::Log::GetClientLogger()->critical(__VA_ARGS__)

#else
#define GRAY_CORE_TRACE(...)
#define GRAY_CORE_INFO(...)
#define GRAY_CORE_WARN(...)
#define GRAY_CORE_ERROR(...)
#define GRAY_CORE_FATAL(...)

//Client Logger
#define GRAY_TRACE(...)
#define GRAY_INFO(...)
#define GRAY_WARN(...)
#define GRAY_ERROR(...)
#define GRAY_FATAL(...)
#endif // DEBUG
