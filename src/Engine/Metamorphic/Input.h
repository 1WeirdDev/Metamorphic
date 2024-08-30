#pragma once

#include "Core.h"
#include "mmafx.h"

namespace Metamorphic{
    class MORPHIC_API Input{
    public:
        void Init();
        void Shutdown();

        void Update();
    private:
        std::array<uint8_t, 400> m_Keys;
    };
}