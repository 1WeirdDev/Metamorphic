#include "mmafx.h"

#include "Component.h"

namespace Metamorphic{
    Component::Component(){}
    Component::~Component(){}

    void Component::Awake(){}
    void Component::Update(){}
    void Component::Draw(){}
}
template <typename t>
void test::Hello(){
    std::cout << "HEllo World" << std::endl;
}