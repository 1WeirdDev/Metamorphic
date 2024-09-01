#include "mmafx.h"

#include "Metamorphic/Input.h"
#include "Metamorphic/Logger.h"

namespace Metamorphic{
    void Input::Init(){
        m_Keys.fill(0);

        MORPHIC_CORE_INFO("Initialized Input System");
    }

    void Input::Shutdown(){
        MORPHIC_CORE_INFO("Shutdown Input System");}

    void Input::Update(){}
}