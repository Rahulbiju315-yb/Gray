#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Gray
{
	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> clientLogger;
		static std::shared_ptr<spdlog::logger> coreLogger;

	public:
		static void Init();
		static std::shared_ptr<spdlog::logger>& GetClientLogger();
		static std::shared_ptr<spdlog::logger>& GetCoreLogger();

	};
}

//Core Logger
#define GRAY_CORE_TRACE(...) Gray::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GRAY_CORE_INFO(...)  Gray::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GRAY_CORE_WARN(...)  Gray::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GRAY_CORE_ERROR(...) Gray::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GRAY_CORE_FATAL(...) Gray::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Logger
#define GRAY_TRACE(...) Gray::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GRAY_INFO(...)  Gray::Log::GetClientLogger()->info(__VA_ARGS__)
#define GRAY_WARN(...)  Gray::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GRAY_ERROR(...) Gray::Log::GetClientLogger()->error(__VA_ARGS__)
#define GRAY_FATAL(...) Gray::Log::GetClientLogger()->fatal(__VA_ARGS__)

