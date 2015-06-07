#pragma once
#ifndef _TANK_HPP_INCLUDED_
#define _TANK_HPP_INCLUDED_

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

        double getPosX() const { return positionX; }
        double getPosY() const { return positionY; }
        double getHullRotation() { return hullRotation; }
        double getVel() { return velocity; }

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
        double turretRot = 0;
        double turretAngleTarget = 0;
        double turretVertX[4], turretVertY[4];
        //tank coordinates
        double tankX[4], tankY[4];
        //moveState is a bit field that represents all move options using an enum
        orienter moveState = orienter(0);
        //a bit field representing the last known state of moves
        orienter lastMoveState = moveState;
        //General Information
        double hullRotation = 0, turretFacing = 0, hullTraverseRate = 0, turretTraverseRate = 0;
        //The angle that the hull and turret are facing, in radians, and the
        //rate at which both rotate in radians per tick
        double positionX = 0, positionY = 0;
        //The X and Y co-ordinates of the tank
        int hp = 0, maxHP = 0;
        //The health points that the tank has currently and the absolute maximum
        //health
        float armour [3];
        //The armour of the tank, in the format front, sides, rear

        //Weapon Information
        int currentAmmo [3], maxAmmo [3], damage [3], penetration [3];
        //Information about the tank's ammo, in the format AP, APCR, HE

        //Engine/Movement Information
        bool moving = false;
        //Is the tank currently moving?
        double horsepower = 0, weight = 0, velocity = 0, maxVel = 0, acceleration = 0, brakeForce = 0;
        //The horsepower of the engine, the weight of the tank, its current speed
        //and its top speed
};

#endif
