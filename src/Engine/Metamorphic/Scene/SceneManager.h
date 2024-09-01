#pragma once

#include "mmafx.h"
#include "Metamorphic/Core.h"

#include "Scene.h"

namespace Metamorphic{
    class MORPHIC_API SceneManager{
    public:
        void Init();
        void Shutdown();

        void Awake();
        void Update();
        void Draw();

        void AddScene(Scene* scene);
        void AddScene(Scene* scene, bool shouldFree);
    private:
        std::vector<Scene*> m_Scenes;
    };
}