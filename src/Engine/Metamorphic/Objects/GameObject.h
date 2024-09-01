#pragma once

#include "mmafx.h"
#include "Metamorphic/Math/Vec2.h"
#include "Component/Component.h"

namespace Metamorphic{
    //class Component;
    class MORPHIC_API GameObject{
    public:
        GameObject();
        ~GameObject();
        friend class Scene;

        void Awake();
        void Start();
        void Update();
        void Draw();

        void AddComponent(Component* component);
        //Will set the components should free
        void AddComponent(Component* component, bool should_free);
    private:
        std::vector<ComponentPointer> m_Components;
    };
    class MORPHIC_API GameObjectPointer{
    public:
        GameObjectPointer(GameObject* gameObject){
            gameObject = gameObject;
        }
        GameObjectPointer(GameObject* gameObject, bool shouldFree){
            m_GameObject = gameObject;
            m_ShouldFree = shouldFree;
        }

        GameObject* GetGameObject() const noexcept{return m_GameObject;}
        bool ShouldFree() const noexcept {return m_ShouldFree;}
    private:
        GameObject* m_GameObject = nullptr;
        bool m_ShouldFree = true;
    };
}