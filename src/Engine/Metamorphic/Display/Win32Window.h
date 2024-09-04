#pragma once

#include "mmafx.h"
#include "Window.h"

namespace Metamorphic{
    class Win32Window : public Window{
    public:
        Win32Window();
        ~Win32Window();

        void Init() override;
        void Shutdown() override;

        void Update() override;

        void SetVsyncEnabled(bool p_Value) override;

        static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        LRESULT CALLBACK HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);

        void SetWindowHandle(HWND hwnd) noexcept{ m_Window = hwnd;}
        HWND GetWindowHandle() const noexcept{return m_Window;}
    private:
        WCHAR  WindowClass[256] = {0};
        WCHAR  WindowTitle[256] = {0};

        HWND m_Window = nullptr;
        HINSTANCE m_HInstance = nullptr;
        WNDCLASSEX wcex;
        MSG m_Msg = {0};
    };
}