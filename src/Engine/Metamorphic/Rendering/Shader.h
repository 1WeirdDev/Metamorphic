#pragma once

#include "Metamorphic/Core.h"

namespace Metamorphic{
    class MORPHIC_API Shader{
    public:
        Shader();
        ~Shader();

        void Start() const;
        void Stop() const;

        void Compile(const char* shaderData);
        void CleanUp();
    }
}