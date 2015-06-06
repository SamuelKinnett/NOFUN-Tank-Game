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
#include <iostream>
//==============================================================================
//Class definition
class Tank
{
    public:
        Tank();
        void update(double);
        void processKeys(GLFWwindow*);
        void draw();

        void moveFwd();
        void moveBwd();
        void moveBrk();

        void traverseLeft();
        void traverseRight();

        void gunRotate(double);

        void RotateTurret(int direction);
        void hit(double, int, int, int);

        double getPosX() { return positionX; }
        double getPosY() { return positionY; }
        double getHullRotation() { return hullRotation; }
        double getVel() { return velocity; }

        constexpr static double PI = 3.14159265359;
        constexpr static double DEG_TO_RAD = PI/180;
        constexpr static double RAD_TO_DEG = 180/PI;
        constexpr static double M_TO_PX = 50/6.75;
        constexpr static double KPH_TO_PXS = 1/3.6*M_TO_PX;
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
            rear = 1<<7,
            gRot = 1<<8
        };
    private:
        double gunRot;
        double gunTraverseRate, gunAngleTarget;
        double gunVertX[4], gunVertY[4];
        //tank coordinates
        double tankX[4], tankY[4];
        //moveState is a bit field that represents all move options using an enum
        orienter moveState;
        //General Information
        double hullRotation, turretFacing, hullTraverseRate, turretTraverseRate;
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
        double horsepower, weight, velocity, maxVel, acceleration, brakeForce;
        //The horsepower of the engine, the weight of the tank, its current speed
        //and its top speed
};

#endif
