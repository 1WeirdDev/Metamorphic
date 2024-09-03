#pragma once

#include "RenderAPI.h"

namespace Metamorphic{
    class MORPHIC_API DirectXRenderAPI : public RenderAPI{
    public:
        DirectXRenderAPI();
        ~DirectXRenderAPI() override;

        void Init() override;
        void Shutdown() override;

        void ClearScreen() override;
    };
}