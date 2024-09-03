#pragma once

#include "Metamorphic/Core.h"

namespace Metamorphic{
    class MORPHIC_API RenderAPI{
    public:
        RenderAPI();
        ~RenderAPI();

        void Init();
        void Shutdown();

        void ClearScreen();
    };
}