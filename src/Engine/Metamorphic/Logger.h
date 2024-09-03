#pragma once

#include "Core.h"
#include "mmafx.h"

namespace Metamorphic{
    class MORPHIC_API Logger{
    public:
        static void Init();
        
        #ifdef METAMORPHIC_USE_SPDLOG
    public:
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
        #endif
    };
}

#ifdef METAMORPHIC_ENGINE_BUILD_DIST

    #define MORPHIC_CORE_ERROR(...)
    #define MORPHIC_CORE_WARN(...)
    #define MORPHIC_CORE_INFO(...)
    #define MORPHIC_CORE_TRACE(...)
    #define MORPHIC_CORE_LOG(...)
    #define MORPHIC_CORE_DEBUG(...)

    #define MORPHIC_ERROR(...)
    #define MORPHIC_WARN(...)	
    #define MORPHIC_INFO(...)	
    #define MORPHIC_TRACE(...)
    #define MORPHIC_FATAL(...)
    #define MORPHIC_LOG(...)
    #define MORPHIC_DEBUG(...)
#else
    #ifdef METAMORPHIC_USE_SPDLOG
        #define MORPHIC_CORE_ERROR(...)	::Metamorphic::Logger::GetCoreLogger()->error(__VA_ARGS__)
        #define MORPHIC_CORE_WARN(...)	::Metamorphic::Logger::GetCoreLogger()->warn(__VA_ARGS__)
        #define MORPHIC_CORE_INFO(...)	::Metamorphic::Logger::GetCoreLogger()->info(__VA_ARGS__)
        #define MORPHIC_CORE_TRACE(...)	::Metamorphic::Logger::GetCoreLogger()->trace(__VA_ARGS__)
        #define MORPHIC_CORE_LOG(...)	::Metamorphic::Logger::GetCoreLogger()->info(__VA_ARGS__)
        #define MORPHIC_CORE_DEBUG(...)	::Metamorphic::Logger::GetCoreLogger()->debug(__VA_ARGS__)

        #define MORPHIC_ERROR(...)	::Metamorphic::Logger::GetClientLogger()->error(__VA_ARGS__)
        #define MORPHIC_WARN(...)		::Metamorphic::Logger::GetClientLogger()->warn(__VA_ARGS__)
        #define MORPHIC_INFO(...)		::Metamorphic::Logger::GetClientLogger()->info(__VA_ARGS__)
        #define MORPHIC_TRACE(...)	::Metamorphic::Logger::GetClientLogger()->trace(__VA_ARGS__)
        #define MORPHIC_LOG(...) ::Metamorphic::Logger::GetClientLogger()->info(__VA_ARGS__)
        #define MORPHIC_DEBUG(...) ::Metamorphic::Logger::GetClientLogger()->debug(__VA_ARGS__)
    #else

        #define MORPHIC_CORE_ERROR(...)
        #define MORPHIC_CORE_WARN(...)
        #define MORPHIC_CORE_INFO(...)
        #define MORPHIC_CORE_TRACE(...)
        #define MORPHIC_CORE_LOG(...)
        #define MORPHIC_CORE_DEBUG(...)

        #define MORPHIC_ERROR(...)
        #define MORPHIC_WARN(...)	
        #define MORPHIC_INFO(...)	
        #define MORPHIC_TRACE(...)
        #define MORPHIC_FATAL(...)
        #define MORPHIC_LOG(...)
        #define MORPHIC_DEBUG(...)
    #endif
#endif