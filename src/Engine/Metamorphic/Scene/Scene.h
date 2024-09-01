#pragma once

#include "mmafx.h"
#include "Metamorphic/Core.h"

#include "Metamorphic/Objects/GameObject.h"

namespace Metamorphic{
    class GameObject;
    class MORPHIC_API Scene{
    public:
        Scene();
        ~Scene();

        //Awake will be called whenever the scene is loaded
        void Awake();
        //TODO: STart
        void Update();
        void Draw();

        void AddGameObject(GameObject* gameObject);
        void AddGameObject(GameObject* gameObject, bool shouldFree);

        friend class SceneManager;
        const std::vector<GameObjectPointer>& GetGameObjects() const noexcept {return m_GameObjects;}
        bool ShouldFree() const noexcept {return m_ShouldFree;}
    private:
        std::vector<GameObjectPointer> m_GameObjects;
        bool m_ShouldFree = true;
    };
}