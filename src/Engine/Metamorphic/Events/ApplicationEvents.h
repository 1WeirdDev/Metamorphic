#pragma once

#include "Event.h"

namespace Metamorphic{
    class MORPHIC_API WindowCloseEvent : public Event{
    public:
        WindowCloseEvent(){}
        EVENT_CLASS_TYPE(ApplicationClose)
        EVENT_CATEGORY(EventCategoryApplication)
    };

    class MORPHIC_API WindowResizedEvent : public Event{
    public:
        WindowResizedEvent(int p_Width, int p_Height) : m_Width(p_Width), m_Height(p_Height){}

        EVENT_CLASS_TYPE(WindowResized)
        EVENT_CATEGORY(EventCategoryApplication)

        int GetWidth() const {return m_Width;}
        int GetHeight() const {return m_Height;}
    private:
        int m_Width = 0;
        int m_Height = 0;
    };
}