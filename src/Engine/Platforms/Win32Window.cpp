#include "mmafx.h"

#include "Metamorphic/Core.h"

#include "Metamorphic/Display/Win32Window.h"
#include "Metamorphic/Events/ApplicationEvents.h"
#include "Metamorphic/Events/InputEvents.h"
#include "Metamorphic/Logger.h"

#include "wrl.h"

//MSG m_Msg = {0};
namespace Metamorphic{
    Window* Window::Create(){
        return new Win32Window();
    }
    Win32Window::Win32Window(){}
    Win32Window::~Win32Window(){
    }

    void Win32Window::Init(){
        wcscpy_s(WindowClass, TEXT("Metamorphic Engine"));
        wcscpy_s(WindowTitle, TEXT("Metamorphic Engine | Direct X"));
        m_HInstance = GetModuleHandle(NULL);

        ZeroMemory(&wcex, sizeof(WNDCLASSEX));
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_OWNDC;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;

        wcex.hCursor = nullptr; //LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground =  nullptr;//(HBRUSH)GetStockObject(NULL_BRUSH);

        wcex.hIcon = nullptr;//LoadIcon(0, IDI_APPLICATION);
        wcex.hIconSm = nullptr;//LoadIcon(0, IDI_APPLICATION);

        wcex.lpszClassName = WindowClass;
        wcex.lpszMenuName = nullptr;

        wcex.hInstance = m_HInstance;
        wcex.lpfnWndProc = Win32Window::WndProc;

        if (!RegisterClassEx(&wcex)) {
            DWORD error = GetLastError();
            MORPHIC_CORE_ERROR("RegisterClassEx failed with error code {0}", error);
            return;
        }

        //Display
        RECT screenRect;
        SystemParametersInfo(SPI_GETWORKAREA, 0, &screenRect, 0);
        int screenWidth = screenRect.right - screenRect.left;
        int screenHeight = screenRect.bottom - screenRect.top;
        
        m_Window = CreateWindowEx(WS_EX_CLIENTEDGE, WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW,
            (screenWidth - m_Data.m_Width) / 2, (screenHeight - m_Data.m_Height) / 2, m_Data.m_Width, m_Data.m_Height, nullptr, nullptr, m_HInstance, this);

        if(!m_Window){
            MORPHIC_CORE_ERROR("Failed to create DirectX Window");
            DWORD error = GetLastError();
            wchar_t  buffer[256];
            FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, 0, buffer, sizeof(buffer), NULL);
            MessageBox(NULL, buffer, L"Error", MB_OK | MB_ICONERROR);
            return;
        }
        ShowWindow(m_Window, SW_SHOWDEFAULT);
        UpdateWindow(m_Window);

        ZeroMemory(&m_Msg, sizeof(MSG));
        m_IsOpen = true;
        MORPHIC_CORE_DEBUG("Created Win32Window");
    }
    void Win32Window::Shutdown(){
        if(m_Window)
            DestroyWindow(m_Window);
        UnregisterClass(WindowClass, m_HInstance);
        m_Window = nullptr;
        MORPHIC_CORE_INFO("Shutdown Win32Window\n");   
    }

    void Win32Window::Update(){
        if(m_IsOpen == false)return;

        if(PeekMessage (&m_Msg, nullptr, 0, 0, PM_REMOVE) != 0){
            TranslateMessage(&m_Msg);
            DispatchMessage(&m_Msg);
        }
    }

    void Win32Window::SetVsyncEnabled(bool enabled){

    }

    LRESULT CALLBACK Win32Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        Win32Window* pThis = nullptr;

        // Retrieve the pointer to the class instance from the window's user data
        if (msg == WM_NCCREATE) {
            pThis = static_cast<Win32Window*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
            pThis->SetWindowHandle(hwnd);

            SetLastError(0);
            if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis)))
            {
                if (GetLastError() != 0){
                    MORPHIC_CORE_DEBUG("FAILED TO SET PTR");
                    return FALSE;
                }
            }
        } else {
            pThis = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        }

        if (pThis) {
            if(pThis->m_IsOpen)
            return pThis->HandleMessage(msg, wParam, lParam);
        }
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    LRESULT CALLBACK Win32Window::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam){
        switch (msg) {
            case WM_DESTROY:
                m_IsOpen = false;
                PostQuitMessage(0);
                return NULL;
            case WM_PAINT: {/*
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(m_Window, &ps);
                // Set the background color to black
                HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
                RECT rect;
                GetClientRect(m_Window, &rect);
                FillRect(hdc, &rect, brush);
                DeleteObject(brush);
                EndPaint(m_Window, &ps);*/
                return NULL;
            }
            default:
                return DefWindowProc(m_Window, msg, wParam, lParam);
        }
    }
}