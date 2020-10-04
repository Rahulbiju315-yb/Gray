#include "grpch.h"
#include "Log.h"

namespace Gray
{
	std::shared_ptr<spdlog::logger> Log::clientLogger;
	std::shared_ptr<spdlog::logger> Log::coreLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		clientLogger = spdlog::stdout_color_mt("Gray Client");
		clientLogger->set_level(spdlog::level::trace);

		coreLogger = spdlog::stderr_color_mt("Gray Core");
		coreLogger->set_level(spdlog::level::trace);
	}

	std::shared_ptr<spdlog::logger>& Gray::Log::GetClientLogger()
	{
		return clientLogger;
	}

	std::shared_ptr<spdlog::logger>& Gray::Log::GetCoreLogger()
	{
		return coreLogger;
	}
}