#pragma once

#include "../../BasicMesh.h"

namespace Metamorphic{
    class MORPHIC_API OpenGLBasicMesh : public BasicMesh{
    public:
        OpenGLBasicMesh();
        ~OpenGLBasicMesh() override;

        void CleanUp() override;
        void Draw() override;

        void Create(void* vertices, void* indices, size_t vertexCount, size_t indexCount, VertexType vertexType, IndexType indexType) override;
    private:
        unsigned int m_VaoId = 0;
        unsigned int m_VboId = 0;
        unsigned int m_EboId = 0;
    };
}