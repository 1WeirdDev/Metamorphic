#pragma once

#include "Core.h"
#include "Application.h"
#include "mmafx.h"
#include "Display/Window.h"
#include "Events/Event.h"
#include "Logger.h"

extern Metamorphic::Application* CreateApplication();

using namespace Metamorphic;
int main(int argc, char** argv){
    Logger::Init();
    MORPHIC_CORE_LOG("Initializing\n");
    Application* application = CreateApplication();
    application->Awake();
    while(application->ShouldUpdate()){
        application->Update();
        application->Draw();
    }
    application->CleanUp();
    delete application;
    MORPHIC_CORE_LOG("Shut Down\n");
}