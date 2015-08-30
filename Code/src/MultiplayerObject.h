#ifndef NTG_MULTIPLAYER_OBJECT_H
#define NTG_MULTIPLAYER_OBJECT_H

class MultiplayerObject {
public:
    virtual void setPos(double x, double y) = 0;

    virtual void setRot(double angle) = 0;

    virtual double getPosX() const = 0;

    virtual double getPosY() const = 0;

    virtual void interpolate(double deltaTime) = 0;

    virtual ~MultiplayerObject();
};

#endif
