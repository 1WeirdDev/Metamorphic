#include "mmafx.h"
#include "GameObject.h"

#include "../Logger.h"
#include "Component/Component.h"

namespace Metamorphic{
    GameObject::GameObject(){
    }
    GameObject::~GameObject(){
        size_t size = m_Components.size();
        for(size_t i = 0; i < size; i++){
            if(m_Components[i].ShouldFree())
                delete m_Components[i].GetComponent();
        }
    }

    void GameObject::Awake(){
        size_t size = m_Components.size();
        for(size_t i = 0; i < size; i++)
            m_Components[i].GetComponent()->Awake();
    }
    void GameObject::Start(){}
    void GameObject::Update(){
        size_t size = m_Components.size();
        for(size_t i = 0; i < size; i++)
            m_Components[i].GetComponent()->Update();
    }
    void GameObject::Draw(){
        size_t size = m_Components.size();
        for(size_t i = 0; i < size; i++)
            m_Components[i].GetComponent()->Draw();
    }
    void GameObject::AddComponent(Component* component){
        ComponentPointer pointer(component);
        m_Components.push_back(pointer);
    }
    //Will set the components should free
    void GameObject::AddComponent(Component* component, bool shouldFree){
        ComponentPointer pointer(component, shouldFree);
        m_Components.push_back(pointer);
    }
}