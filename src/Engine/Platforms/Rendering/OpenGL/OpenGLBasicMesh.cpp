//This gets included by the header file so dont worry about includes
//this is not included by the compiler
#include "mmafx.h"
#include "Metamorphic/Logger.h"

#include "Metamorphic/Rendering/Mesh/APIS/OpenGL/OpenGLBasicMesh.h"
#include <GL/glew.h>

namespace Metamorphic{
    BasicMesh* BasicMesh::Create(){
        return new OpenGLBasicMesh();
    }
    OpenGLBasicMesh::OpenGLBasicMesh(){}
    OpenGLBasicMesh::~OpenGLBasicMesh(){}

    void OpenGLBasicMesh::CleanUp(){

    }
    void OpenGLBasicMesh::Draw(){
        if(m_IsCreated == false)return;

        glBindVertexArray(m_VaoId);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
    }
    void OpenGLBasicMesh::Create(void* vertices, void* indices, size_t vertexCount, size_t indexCount, VertexType vertexType, IndexType indexType){
        glGenVertexArrays(1, &m_VaoId);
        glGenBuffers(1, &m_VboId);
        glGenBuffers(1, &m_EboId);

        glBindVertexArray(m_VaoId);
        glBindBuffer(GL_ARRAY_BUFFER, m_VboId);

        size_t vertexDataSize = vertexCount;
        GLenum glVertexType = 0;
        switch(vertexType){
            case VertexTypeUnsignedChar:
                vertexDataSize *= sizeof(uint8_t);
                glVertexType = GL_UNSIGNED_BYTE;
                break;
            case VertexTypeChar:
                vertexDataSize *= sizeof(int8_t);
                glVertexType = GL_BYTE;
                break;
            case VertexTypeUnsignedShort:
                vertexDataSize *= sizeof(uint16_t);
                glVertexType = GL_UNSIGNED_SHORT;
                break;
            case VertexTypeShort:
                vertexDataSize *= sizeof(int16_t);
                glVertexType = GL_SHORT;
                break;
            case VertexTypeUnsignedInt:
                vertexDataSize *= sizeof(uint32_t);
                glVertexType = GL_UNSIGNED_INT;
                break;
            case VertexTypeInt:
                vertexDataSize *= sizeof(int32_t);
                glVertexType = GL_INT;
                break;
            case VertexTypeFloat:
                vertexDataSize *= sizeof(float);
                glVertexType = GL_FLOAT;
                break;
        }
        glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, glVertexType, false, 0, 0);

        //Indices
        size_t indexDataSize = indexCount;
        switch(indexType){
            case IndexTypeUnsignedChar:
                indexDataSize *= sizeof(uint8_t);
                break;
            case IndexTypeUnsignedShort:
                indexDataSize *= sizeof(uint16_t);
                break;
            case IndexTypeUnsignedInt:
                indexDataSize *= sizeof(int32_t);
                break;
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EboId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indices, GL_STATIC_DRAW);

        m_IsCreated = true;
        MORPHIC_CORE_DEBUG("Created Opengl Mesh Vao {0} Vbo {1} Ebo {2} Vertex Count {3}", m_VaoId, m_VaoId, m_EboId, vertexCount);
    }
}