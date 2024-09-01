#include "mmafx.h"

#include "Scene.h"

#include "Metamorphic/Logger.h"

namespace Metamorphic{
    Scene::Scene(){}
    Scene::~Scene(){
        size_t size = m_GameObjects.size();
        for(size_t i = 0; i < size; i++){
            if(m_GameObjects[i].ShouldFree())
                delete m_GameObjects[i].GetGameObject();
        }
    }

    void Scene::Awake(){
        size_t size = m_GameObjects.size();
        for(size_t i = 0; i < size; i++){
            m_GameObjects[i].GetGameObject()->Awake();
        }
    }
    void Scene::Update(){
        size_t size = m_GameObjects.size();
        for(size_t i = 0; i < size; i++){
            m_GameObjects[i].GetGameObject()->Update();
        }}
    void Scene::Draw(){
        size_t size = m_GameObjects.size();
        for(size_t i = 0; i < size; i++){
            m_GameObjects[i].GetGameObject()->Draw();
        }
    }

    void Scene::AddGameObject(GameObject* gameObject){
        GameObjectPointer pointer(gameObject);
        m_GameObjects.push_back(pointer);
        gameObject->Awake();
    }
    void Scene::AddGameObject(GameObject* gameObject, bool shouldFree){
        GameObjectPointer pointer(gameObject, shouldFree);
        m_GameObjects.push_back(pointer);
        gameObject->Awake();
    }
}