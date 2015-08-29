#ifndef TANK_HPP_INCLUDED_
#define TANK_HPP_INCLUDED_

//Included dependencies
#include "AABB.hpp"
#include "MultiplayerObject.hpp"
#include "Drawable.hpp"
#include <math.h>
#include <GLFW/glfw3.h>
#include <iostream>

//A class describing a tank
class Tank : public MultiplayerObject, public Drawable
{
    public:
        Tank();
        Tank(double, double, double, double, double, double);
        virtual ~Tank()
        {

        }

        void update(double);
        void processKeys(GLFWwindow*, double, double);
        void draw();

        void setPos(double x, double y);
        void setRot(double angle);

        void moveFwd();
        void moveBwd();
        void moveBrk();

        void traverseLeft();
        void traverseRight();

        void turretRotate(double);
        void turretRotateTo(double);
        void target(const MultiplayerObject&);

        double getPosX() const { return _positionX; }
        double getPosY() const { return _positionY; }
        double getHullRotation() { return _hullRotation; }
        double getVel() { return _velocity; }

        void interpolate(double deltaTime);

        const static double PI;
        const static double DEG_TO_RAD;
        const static double RAD_TO_DEG;
        const static double M_TO_PX;
        const static double KPH_TO_PXS;
    protected:
        void setAcc(double);
        enum orienter
        {
            LEFT = 1<<0,
            RIGHT = 1<<1,
            FWD = 1<<2,
            BWD = 1<<3,
            BRAKE = 1<<4,
            FRONT = 1<<5,
            SIDES = 1<<6,
            REAR = 1<<7,
            T_ROT = 1<<8
        };
    private:
        double _turretRot = 0;
        double _turretAngleTarget = 0;
        double _turretVertX[4], _turretVertY[4];
        //tank coordinates
        double _tankX[4], _tankY[4];
        //_moveState is a bit field that represents all move options using an enum
        orienter _moveState = orienter(0);
        //a bit field representing the last known state of moves
        orienter _lastMoveState = _moveState;

        //General Information

        //The angle that the hull and turret are facing, in radians, and the
        //rate at which both rotate in radians per tick
        double _hullRotation = 0, _turretFacing = 0, _hullTraverseRate = 0, _turretTraverseRate = 0;
        //The X and Y co-ordinates of the tank
        double _positionX = 0, _positionY = 0;
        //The health points that the tank has currently and the absolute maximum
        int _hp = 0, _maxHP = 0;
        //The armour of the tank, in the format front, sides, rear
        float _armour [3];
        //Weapon Information
        //Information about the tank's ammo, in the format AP, APCR, HE
        int _currentAmmo [3], _maxAmmo [3], _damage [3], _penetration [3];

        //Engine/Movement Information
        //Is the tank currently _moving?
        bool _moving = false;
        //The horsepower of the engine, the weight of the tank, its current speed
        //and its top speed
        double _horsepower = 0, _weight = 0, _velocity = 0, _maxVel = 0, _acceleration = 0, _brakeForce = 0;
};

#endif
