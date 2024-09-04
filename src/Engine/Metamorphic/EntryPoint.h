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
#ifdef METAMORPHIC_ENGINE_BUILD_DIST
#define METAMORPHIC_MAIN int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#else
#define METAMORPHIC_MAIN int main(int argc, char** argv)
#endif

METAMORPHIC_MAIN{
    Logger::Init();
    Application* application = CreateApplication();
    Time::Init();
    application->Awake();
    MORPHIC_CORE_LOG("Created Application");
    while(application->ShouldUpdate()){
        Time::Update();
        application->Update();
        application->Draw();
    }
    application->Shutdown();
    delete application;
    MORPHIC_CORE_LOG("Shut Down\n");
}