#pragma once

#include "Metamorphic/Objects/Component/Component.h"

namespace Metamorphic{
    enum VertexType{
        //8 Bits
        VertexTypeChar=0,
        VertexTypeUnsignedChar,
        
        //16 Bits
        VertexTypeShort,
        VertexTypeUnsignedShort,

        //32 Bits
        VertexTypeInt,
        VertexTypeUnsignedInt,

        VertexTypeFloat
    };

    enum IndexType{
        //8 Bits
        IndexTypeUnsignedChar,
        
        //16 Bits
        IndexTypeUnsignedShort,

        //32 Bits
        IndexTypeUnsignedInt,
    };

    //Only contains vertices and indices
    //No normals or texture coords
    class MORPHIC_API Mesh : public Component{
    public:
        Mesh(){}
        ~Mesh(){}

        virtual void CleanUp(){}
    protected:
        void* m_Vertices = nullptr;
        void* m_Indices = nullptr;
        VertexType m_VertexDataType = VertexTypeUnsignedShort;
        IndexType m_IndexDataType = IndexTypeUnsignedShort;
        bool m_IsCreated = false;
    };
}