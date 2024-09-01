#pragma once

#include <iostream>
#include <fstream>

#include <functional>
#include <algorithm>

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
#else
#error Invalid Metamorphic Platform specified
#endif