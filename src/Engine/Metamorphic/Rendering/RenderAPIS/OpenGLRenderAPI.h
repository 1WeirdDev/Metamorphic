#pragma once

#include "../RenderAPI.h"

namespace Metamorphic{
    class MORPHIC_API OpenGLRenderAPI : public RenderAPI{
    public:
        OpenGLRenderAPI(Application& p_App);
        ~OpenGLRenderAPI() override;

        void Init() override;
        void Shutdown() override;

        void ClearScreen() override;
        
        void OnWindowResize(WindowResizedEvent& e) override;
    };
}