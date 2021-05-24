#pragma once

#include "Eros/Core/Base.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)


namespace Eros {

	//logging class
	class Log
	{
	public:
		static void Init();
		static void Shutdown();

		//getters
		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define EROSIONSIM_CORE_TRACE(...)		::Eros::Log::getCoreLogger()->trace(__VA_ARGS__)
#define EROSIONSIM_CORE_INFO(...)		::Eros::Log::getCoreLogger()->info(__VA_ARGS__)
#define EROSIONSIM_CORE_WARN(...)		::Eros::Log::getCoreLogger()->warn(__VA_ARGS__)
#define EROSIONSIM_CORE_ERROR(...)		::Eros::Log::getCoreLogger()->error(__VA_ARGS__)
#define EROSIONSIM_CORE_CRITICAL(...)   ::Eros::Log::getCoreLogger()->critical(__VA_ARGS__)
										
// Client log macros					
#define EROSIONSIM_TRACE(...)			::Eros::Log::getClientLogger()->trace(__VA_ARGS__)
#define EROSIONSIM_INFO(...)			::Eros::Log::getClientLogger()->info(__VA_ARGS__)
#define EROSIONSIM_WARN(...)			::Eros::Log::getClientLogger()->warn(__VA_ARGS__)
#define EROSIONSIM_ERROR(...)			::Eros::Log::getClientLogger()->error(__VA_ARGS__)
#define EROSIONSIM_FATAL(...)			::Eros::Log::getClientLogger()->critical(__VA_ARGS__)