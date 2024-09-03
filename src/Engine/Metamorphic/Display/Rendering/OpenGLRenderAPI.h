#pragma once

#include "RenderAPI.h"

namespace Metamorphic{
    class MORPHIC_API OpenGLRenderAPI : public RenderAPI{
    public:
        OpenGLRenderAPI();
        ~OpenGLRenderAPI() override;

        void Init() override;
        void Shutdown() override;
        
        void ClearScreen() override;
    };
}