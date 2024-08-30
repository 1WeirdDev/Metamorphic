#pragma once

#ifndef METAMORPHIC_ENGINE_BUILD_DIST
#define MORPHIC_ASSERT(x, ...) if(!x){printf(__VA_ARGS__);__debugbreak();}
#else
#define MORPHIC_ASSERT(x, ...) x
#endif

#ifdef METAMORPHIC_ENGINE_STATIC
#define MORPHIC_API
#else
    #ifdef METAMORPHIC_ENGINE_EXPORTS
    #define MORPHIC_API __declspec(dllexport)
    #else
    #define MORPHIC_API __declspec(dllimport)
    #endif
#endif