#include "mmafx.h"
#include "SceneManager.h"

#include "Metamorphic/Logger.h"

namespace Metamorphic{
    void SceneManager::Init(){
        m_Scenes.resize(0);
        MORPHIC_CORE_INFO("Initialized Scene Manager");
    }
    void SceneManager::Shutdown(){
        size_t size = m_Scenes.size();
        for(size_t i = 0; i < size; i++){
            if(m_Scenes[i]->ShouldFree())
                delete m_Scenes[i];
        }

        m_Scenes.resize(0);
        MORPHIC_CORE_INFO("Shutdown Scene Manager");
    }

    void SceneManager::Awake(){
        size_t size = m_Scenes.size();
        for(size_t i = 0; i < size; i++)
            m_Scenes[i]->Awake();
    }
    void SceneManager::Update(){
        size_t size = m_Scenes.size();
        for(size_t i = 0; i < size; i++)
            m_Scenes[i]->Update();
    }
    void SceneManager::Draw(){
        size_t size = m_Scenes.size();
        for(size_t i = 0; i < size; i++)
            m_Scenes[i]->Draw();
    }

    void SceneManager::AddScene(Scene* scene){
        m_Scenes.push_back(scene);
        scene->Awake();
    }
    void SceneManager::AddScene(Scene* scene, bool shouldFree){
        scene->m_ShouldFree = shouldFree;
        m_Scenes.push_back(scene);
        scene->Awake();
    }
}