#include "mmafx.h"

#include "Metamorphic/Core.h"

#include "Metamorphic/Display/Window.h"
#include "Metamorphic/Events/ApplicationEvents.h"
#include "Metamorphic/Events/InputEvents.h"
#include "Metamorphic/Logger.h"

namespace Metamorphic{
    void Window::Init(){
        const int maxNameString = 256;
        WCHAR  WindowClass[maxNameString];
        WCHAR  WindowTitle[maxNameString];

        wcscpy_s(WindowClass, TEXT("HELLO DirectX"));
        wcscpy_s(WindowTitle, TEXT("Window1"));

        WNDCLASSEX wcex;

        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;

        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground =  (HBRUSH)GetStockObject(NULL_BRUSH);

        wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
        wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);

        wcex.lpszClassName = WindowClass;
        wcex.lpszMenuName = nullptr;

        wcex.hInstance = GetModuleHandle(NULL);
        wcex.lpfnWndProc = DefWindowProc;

        RegisterClassEx(&wcex);

        //Display
        int WindowWidth =1280;
        int WindowHeight = 720;
        HWND hWND = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, GetModuleHandle(NULL), nullptr);

        ShowWindow(hWND, SW_SHOW);
        m_IsOpen = true;

        /*
        MSG msg = { 0 };
        while(msg.message != WM_QUIT){
            if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        */
    }
    void Window::Shutdown(){

    }

    void Window::Update(){
        MSG msg = {0};
        while(msg.message != WM_QUIT){
            if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        m_IsOpen = false;
    }
    void Window::SetEventHandlerCallback(EventHandlerCallback p_EventHandler){
        m_Data.m_EventCallback = p_EventHandler;
    }
}