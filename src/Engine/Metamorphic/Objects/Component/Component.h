#pragma once

#include "Metamorphic/Core.h"

namespace Metamorphic{
    class MORPHIC_API Component{
    public:
        Component();
        virtual ~Component();

        //All components are allowed to be shared with different game objects
        //with only one instance
        //This might be depricated in the future

        //Will be called every time the game object awake is called and if it is added onto object
        virtual void Awake();
        virtual void Update();
        virtual void Draw();
    public:
        friend class GameObject;
    };

    class MORPHIC_API ComponentPointer{
    public:
        ComponentPointer(Component* component){
            m_Component = component;
        }
        ComponentPointer(Component* component, bool shouldFree){
            m_Component = component;
            m_ShouldFree = shouldFree;
        }

        Component* GetComponent() const noexcept{return m_Component;}
        bool ShouldFree() const noexcept{return m_ShouldFree;}
    private:
        Component* m_Component = nullptr;
        bool m_ShouldFree = true;
    };
}