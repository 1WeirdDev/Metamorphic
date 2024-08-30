#pragma once

namespace Metamorphic{
    template <typename TYPE>
    class Vec2{
    public:
        Vec2();
        Vec2(TYPE x, TYPE y){
            m_X = x;
            m_Y = y;
        }

        TYPE GetX() const {return m_X;}
        TYPE GetY() const {return m_Y;}
    private:
        TYPE m_X;
        TYPE m_Y;
    };
}