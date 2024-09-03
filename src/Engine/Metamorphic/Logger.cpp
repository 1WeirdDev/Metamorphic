#include "mmafx.h"
#include "Logger.h"

namespace Metamorphic{
	#ifdef METAMORPHIC_USE_SPDLOG
    std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;
	
    void Logger::Init(){

		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("Metamorphic");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("Application");
		s_ClientLogger->set_level(spdlog::level::trace);
    }
	#else
	void Logger::Init(){}
	
	#endif
}