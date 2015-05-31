#include <math.h>
#include "../include/tank.h"

Tank::Tank()
{
    moveState = orienter(0);
    hullFacing = 0;
    hullTraverseRate = 90 * DEG_TO_RAD;
    positionX = positionY = 0;
    hp = maxHP = 1000;
    moving = false;
    horsepower = 5000;
    brakeForce = 100;
    weight = 50;
    currentSpeed = 0;
    topSpeed = 500;
    tankX[0] = -15; tankX[1] = 15; tankX[2] = 15; tankX[3] = -15;
    tankY[0] = -25; tankY[1] =  -25; tankY[2] = 25; tankY[3] = 25;
}

void Tank::setAcc(double deltaTime)
{
    //TODO: calculate acceleration based on
    //horsepower, velocity, weight, gear ratio, rpm, ground resistance, ground grip, torque, ...
    acceleration = (horsepower / weight) * deltaTime;
}

void Tank::moveFwd()
{
    moveState = orienter(moveState | orienter::fwd);
}
void Tank::moveBwd()
{
    moveState = orienter(moveState | orienter::bwd);
}
void Tank::moveBrk()
{
    moveState = orienter(moveState | orienter::brake);
}
void Tank::traverseLeft()
{
    moveState = orienter(moveState | orienter::left);
}
void Tank::traverseRight()
{
    moveState = orienter(moveState | orienter::right);
}

//This method should be called every time the main update loop runs and updates
//the tank's variables
//deltaTime is used to make a simple Euler Integrator to ensure framerate
//independent movement.
void Tank::update(double deltaTime)
{
    //sets acceleration based on various parameters
    setAcc(deltaTime);
    if(moveState & brake)
    {
        moving = false;
        currentSpeed *= pow(brakeForce, -deltaTime);
    }
    else if(moveState & fwd) //forward
    {
        moving = true;
        currentSpeed += acceleration;
        if(currentSpeed > topSpeed)
            currentSpeed = topSpeed;
    }
    else if(moveState & bwd) //backward, only allow one motion
    {
        moving = true;
        currentSpeed -= acceleration;
        if(currentSpeed < -topSpeed/4)
            currentSpeed = -topSpeed/4;
    }
    else //stationary
    {
        moving = false;
        currentSpeed *= pow(1.95, -deltaTime);
    }
    if(moveState & left) //turn left
    {
        hullFacing += hullTraverseRate * deltaTime;
        while(hullFacing > 2*PI)
            hullFacing -= 2*PI;
    }
    if(moveState & right) //turn right
    {
        hullFacing -= hullTraverseRate * deltaTime;
        while(hullFacing < 0)
            hullFacing += 2*PI;
    }

    //Move the tank
    positionX += -sin(hullFacing) * currentSpeed * deltaTime;
    positionY += cos(hullFacing) * currentSpeed * deltaTime;
    moveState = orienter(0); //reset moveState to contain bits set
}

void Tank::draw()
{
    glPushMatrix();
    glTranslatef(positionX, positionY, 0.0f);
    glRotatef(hullFacing * Tank::RAD_TO_DEG, 0.0f, 0.0f, 1.0f);

    glBegin(GL_QUADS);
    {
        for(int i = 0; i < 4; i++)
        {
            glVertex2d(tankX[i], tankY[i]);
        }
    }
    glEnd();
    glPopMatrix();
}

void Tank::processKeys(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        moveFwd();
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        moveBwd();
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        moveBrk();
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        traverseLeft();
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        traverseRight();
    }
}

//This method handles traversing the turret, given a direction
//1 = right, 0 = left
void Tank::RotateTurret(int direction)
{
    switch (direction)
    {
        case (orienter(right)):
            if (turretFacing + turretTraverseRate < (360 * DEG_TO_RAD))
                turretFacing += turretTraverseRate;
            else
                turretFacing = (turretFacing + turretTraverseRate) -
                               (360 * DEG_TO_RAD);
            break;

        case (orienter(left)):
            if (turretFacing - turretTraverseRate > 0)
                turretFacing -= turretTraverseRate;
            else
                turretFacing = (turretFacing - turretTraverseRate) +
                               (360 * DEG_TO_RAD);
            break;
        default:
            throw 0;
    }
}

//This method handles the tank being hit by an enemy shot
//angleOfShot is the angle of the enemy shell and is given in radians.
//damage and penetration are, obviously, the damage and penetration of the
//enemy shot.
//areaHit details the area of the tank that was hit. 0 = front, 1 = sides,
//2 = rear.
void Tank::hit(double angleOfShot, int damage, int penetration, int areaHit)
{
   //TODO: Everything here, currently in progress
}
