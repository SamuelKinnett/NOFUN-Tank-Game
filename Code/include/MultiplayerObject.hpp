#pragma once
#ifndef _MULTIPLAYEROBJECT_HPP_INCLUDED_
#define _MULTIPLAYEROBJECT_HPP_INCLUDED_

#include "Drawable.hpp"

class MultiplayerObject
{
    public:
        virtual void setPos(double x, double y) = 0;
        virtual void setRot(double angle) = 0;
        virtual double getPosX() const = 0;
        virtual double getPosY() const = 0;
        virtual void interpolate(double deltaTime) = 0;
};

#endif