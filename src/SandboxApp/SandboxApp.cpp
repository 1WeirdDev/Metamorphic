#include "Metamorphic.h"

using namespace Metamorphic;
class SandboxApp : Metamorphic::Application{
public:
    SandboxApp(){
        MORPHIC_LOG("Sandbox INit");
        MORPHIC_LOG("{0} {1}", sizeof(GameObject*), sizeof(GameObjectPointer));
    }
    ~SandboxApp(){
        MORPHIC_LOG("Sandbox Cleaning Up");
    }

    void OnAwake() override{
        m_SceneManager.AddScene(&scene, false);
        scene.AddGameObject(&obj, false);
        obj.AddComponent(&m_BasicMesh, false);
    }

    Scene scene;
    Metamorphic::GameObject obj;
    BasicMesh<float, int> m_BasicMesh;
};
Metamorphic::Application* CreateApplication(){
    return (Metamorphic::Application*)new SandboxApp();
}