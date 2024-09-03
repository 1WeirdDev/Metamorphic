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
        /*
        m_SceneManager.AddScene(&scene, false);
        scene.AddGameObject(&obj, false);
        obj.AddComponent(&m_BasicMesh, false);*/
    }

    void OnUpdate() override{
        //MORPHIC_DEBUG("FPS : {0}", (1.0f / Time::GetDeltaTime()));
    }
    /*
    Scene scene;
    Metamorphic::GameObject obj;
    BasicMesh<float, int> m_BasicMesh;
    */
};
Metamorphic::Application* CreateApplication(){
    return (Metamorphic::Application*)new SandboxApp();
}