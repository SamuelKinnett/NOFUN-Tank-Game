#pragma once
#ifndef _MULTIPLAYEROBJECT_HPP_INCLUDED_
#define _MULTIPLAYEROBJECT_HPP_INCLUDED_

#include "Drawable.hpp"

class MultiplayerObject : public Drawable
{
    public:
        virtual void setPos(double x, double y) = 0;
        virtual void setRot(double angle) = 0;
        virtual double getPosX() = 0;
        virtual double getPosY() = 0;
};

#endif