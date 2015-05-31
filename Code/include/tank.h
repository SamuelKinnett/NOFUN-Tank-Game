//A class describing a tank

//==============================================================================
//Include guard
#ifndef __TANK_INCLUDED__
#define __TANK_INCLUDED__
//==============================================================================
//Included dependencies
#include "AABB.h"
#include <math.h>
#include <GLFW/glfw3.h>
//==============================================================================
//Class definition
class Tank
{
    public:
        Tank();
        void update(double);
        void draw();

        void moveFwd();
        void moveBwd();
        void moveBrk();

        void traverseLeft();
        void traverseRight();

        void RotateTurret(int direction);
        void hit(double, int, int, int);

        double getPosX() { return positionX; }
        double getPosY() { return positionY; }
        double getHullRotation() { return hullFacing; }

        constexpr static double PI = 3.14159265359;
        constexpr static double DEG_TO_RAD = PI/180;
        constexpr static double RAD_TO_DEG = 180/PI;
    protected:
        void setAcc(double);
        enum orienter
        {
            left = 1<<0,
            right = 1<<1,
            fwd = 1<<2,
            bwd = 1<<3,
            brake = 1<<4,
            front = 1<<5,
            sides = 1<<6,
            rear = 1<<7
        };
    private:

        //tank coordinates
        double tankX[4], tankY[4];
        //moveState is a bit field that represents all move options using an enum
        orienter moveState;
        //General Information
        double hullFacing, turretFacing, hullTraverseRate, turretTraverseRate;
        //The angle that the hull and turret are facing, in radians, and the
        //rate at which both rotate in radians per tick
        double positionX, positionY;
        //The X and Y co-ordinates of the tank
        int hp, maxHP;
        //The health points that the tank has currently and the absolute maximum
        //health
        float armour [3];
        //The armour of the tank, in the format front, sides, rear

        //Weapon Information
        int currentAmmo [3], maxAmmo [3], damage [3], penetration [3];
        //Information about the tank's ammo, in the format AP, APCR, HE

        //Engine/Movement Information
        bool moving;
        //Is the tank currently moving?
        float horsepower, weight, currentSpeed, topSpeed, acceleration, brakeForce;
        //The horsepower of the engine, the weight of the tank, its current speed
        //and its top speed
};

#endif
