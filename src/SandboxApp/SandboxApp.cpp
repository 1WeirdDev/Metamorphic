
//#define METAMORPHIC_USE_OPENGL
#include "Metamorphic.h"

using namespace Metamorphic;
class SandboxApp : Metamorphic::Application{
public:
    SandboxApp(){
        MORPHIC_LOG("Sandbox INit");
    }

    void OnShutdown() override{
        
    }

    void OnAwake() override{
        m_Window->SetVsyncEnabled(true);
        m_BasicMesh = BasicMesh::Create();

        m_SceneManager.AddScene(&scene, false);
        scene.AddGameObject(&obj, false);
        obj.AddComponent(m_BasicMesh);

        char vertices[8]{
            0,0,
            0,1,
            1,0,
            1,1
        };

        unsigned char indices[6]{
            0,1,2,2,1,3
        };
        m_BasicMesh->Create(&vertices, &indices, 8, 6, VertexTypeChar, IndexTypeUnsignedChar);
    }

    void OnUpdate() override{
        //MORPHIC_DEBUG("FPS : {0}", (1.0f / Time::GetDeltaTime()));
    }
    Scene scene;
    Metamorphic::GameObject obj;
    BasicMesh* m_BasicMesh = nullptr;
    
};
Metamorphic::Application* CreateApplication(){
    return (Metamorphic::Application*)new SandboxApp();
}