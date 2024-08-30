#pragma once

#include "mmafx.h"
#include "Metamorphic/Core.h"

namespace Metamorphic{
    enum EventType{
        EventTypeNone = 0,
        ApplicationClose,   WindowLostFocus,    WindowFocused,  WindowMoved, WindowResized,
        MouseDown, MouseUp, MouseMove,  ScrollWheelUp, ScrollWheelDown,
        KeyButtonDown, KeyButtonUp,
    };
    enum EventCategoryType{
        EventCategoryNone = 0,
        EventCategoryApplication = 1 << 1,
        EventCategoryInput = 1 << 2,
        EventCategoryKeyboard = 1 << 3,
        EventCategoryMouse = 1 << 4,
        EventCategoryButton = 1 << 4,
    };
#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType(){return EventType::##type;}\
                                virtual int GetEventType(){return type;}\
                                virtual const char* GetEventName(){return #type;}
                                
#define EVENT_CATEGORY(type)    virtual int GetEventCategoryType(){return type;}\
                                virtual const char* GetEventCategoryName(){return #type;}
    class MORPHIC_API Event{
    public:
        Event(){}
        friend class EventDispatcher;

        EVENT_CLASS_TYPE(EventTypeNone)
        EVENT_CATEGORY(EventCategoryNone)
        
        bool IsHandled() const {return m_IsHandled;}
    private:
        bool m_IsHandled = false;
    };

    class MORPHIC_API EventDispatcher{
    public:
		template<typename T>
        using EventFN = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& e) : m_Event(e){}

        template <typename T>
        bool Dispatch(EventFN<T> p_Func){
            if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_IsHandled = p_Func(*(T*)&m_Event);
				return true;
			}

			return false;
        }
    private:
        Event& m_Event;
    };
}