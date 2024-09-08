#pragma once

#include "../Mesh.h"

//Base
//
namespace Metamorphic{
    //Only contains vertices and indices
    //No normals or texture coords
    class MORPHIC_API BasicMesh : public Mesh{
    public:
        static BasicMesh* Create();

        BasicMesh(){}
        virtual ~BasicMesh() override{}

        //virtual void Create(char vertices, unsigned char indices, size_t vertex_count, size_t index_count){}
        virtual void Create(void* vertices, void* indices, size_t vertexCount, size_t indexCount, VertexType vertexType, IndexType indexType){}
    };
}