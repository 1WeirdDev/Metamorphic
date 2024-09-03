#pragma once

#include "Metamorphic/Core.h"

namespace Metamorphic{
    class MORPHIC_API RenderAPI{
    public:
        static RenderAPI* CreateRenderAPI();

        RenderAPI(){}
        virtual ~RenderAPI(){}

        virtual void Init(){}
        virtual void Shutdown(){}

        virtual void ClearScreen(){}
    };
}