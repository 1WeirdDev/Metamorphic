#pragma once

#include "Metamorphic/Objects/Component/Component.h"
#include "Metamorphic/Logger.h"

namespace Metamorphic{
    //Can be types of any number types like int,float
    //Template classes dont need to be exported
    template <typename VERTEX_TYPE, typename INDEX_TYPE>
    class BasicMesh : public Component{
    public:
        ~BasicMesh() override{
            
        }
        void Draw() override{
            if(!m_Created)return;

        }

        void CreateMesh();
    private:
        VERTEX_TYPE* vertices = nullptr;
        INDEX_TYPE* indices = nullptr;
        bool m_Created = false;
    };
}

#ifdef METAMORPHIC_USE_OPENGL
#include "Platforms/Rendering/BasicMesh.cpp"
#endif