//A class describing a tank

//==============================================================================
//Include guard
#ifndef __TANK_INCLUDED__
#define __TANK_INCLUDED__
//==============================================================================
//Included dependencies
#include "AABB.h"
//==============================================================================
//Class definition
class Tank {
    public:
        Tank();
        void Move(int, float);
        void Traverse(int);
        void Update(float);
        void RotateTurret(int);
        void Hit(float, int, int, int);
        double getPosX() { return positionX; }
        double getPosY() { return positionY; }
    protected:
        void setAcc(float);
    private:
        //General Information
        float hullFacing, turretFacing, hullTraverseRate, turretTraverseRate;
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
        float horsepower, weight, currentSpeed, topSpeed, acceleration;
        //The horsepower of the engine, the weight of the tank, its current speed
        //and its top speed
        const double PI = 3.14159265359;
        const double DEG_TO_RAD = PI/180;
        const double RAD_TO_DEG = 180/PI;
};

#endif
