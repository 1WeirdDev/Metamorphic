#pragma once

#include "Core.h"
#include "Application.h"
#include "mmafx.h"
#include "Display/Window.h"
#include "Events/Event.h"
#include "Logger.h"
#include "Time.h"

extern Metamorphic::Application* CreateApplication();

using namespace Metamorphic;
int main(int argc, char** argv){
    Logger::Init();
    Application* application = CreateApplication();
    MORPHIC_CORE_LOG("Created Application");
    Time::Init();
    application->Awake();
    while(application->ShouldUpdate()){
        Time::Update();
        application->Update();
        application->Draw();
    }
    application->Shutdown();
    delete application;
    MORPHIC_CORE_LOG("Shut Down\n");
}