#ifndef MULTIPLAYEROBJECT_HPP_INCLUDED_
#define MULTIPLAYEROBJECT_HPP_INCLUDED_

class MultiplayerObject
{
    public:
        virtual void setPos(double x, double y) = 0;
        virtual void setRot(double angle) = 0;
        virtual double getPosX() const = 0;
        virtual double getPosY() const = 0;
        virtual void interpolate(double deltaTime) = 0;
        virtual ~MultiplayerObject();
};

#endif
