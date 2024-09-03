#pragma once

#include <iostream>
#include <fstream>

#include <functional>
#include <algorithm>

#include <chrono>
#include <string>

#include <array>
#include <vector>

#include <cstdint>

#if METAMORPHIC_PLATFORM == Windows
    #ifndef UNICODE
    #define UNICODE
    #define UNICODE_WAS_UNDEFINED
    #endif

    #include <Windows.h>

    #ifdef UNICODE_WAS_UNDEFINED
    #undef UNICODE
    #endif
    #include <wchar.h>
    //#include <wrl.h> // For Microsoft's WRL (Windows Runtime Library)

    #ifdef METAMORPHIC_USE_DIRECTX
        #include <d3d12.h>
        #include <dxgi1_6.h>
    #endif
#else
#error Invalid Metamorphic Platform specified
#endif

#if METAMORPHIC_USE_SPDLOG
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#endif

#if METAMORPHIC_USE_GLFW

#endif