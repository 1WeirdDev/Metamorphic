#pragma once

#include "Event.h"

namespace Metamorphic{
    class MORPHIC_API KeyDownEvent : public Event{
    public:
        KeyDownEvent(int p_Key, int p_Mods, bool p_Repeat) : key(p_Key), mods(p_Mods), repeat(p_Repeat) {}

        EVENT_CLASS_TYPE(KeyButtonDown)
        EVENT_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

        int GetKey() const {return key;}
        int GetMods() const {return mods;}
        int GetRepeat() const {return repeat;}
    private:
        int key = 0;
        int mods = 0;
        bool repeat = false;
    };
    class MORPHIC_API KeyUpEvent : public Event{
    public:
        KeyUpEvent(int p_Key, int p_Mods) : key(p_Key), mods(p_Mods){}

        EVENT_CLASS_TYPE(KeyButtonUp)
        EVENT_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

        int GetKey() const {return key;}
        int GetMods() const {return mods;}
    private:
        int key = 0;
        int mods = 0;
    };
}