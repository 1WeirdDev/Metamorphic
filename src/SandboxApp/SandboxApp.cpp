#include "Metamorphic.h"

class SandboxApp : Metamorphic::Application{
public:
    SandboxApp(){
        MORPHIC_LOG("Sandbox INit");
        Metamorphic::GameObject obj;
    }
    ~SandboxApp(){
        MORPHIC_LOG("Sandbox Cleaning Up");
    }
};
Metamorphic::Application* CreateApplication(){
    return (Metamorphic::Application*)new SandboxApp();
}