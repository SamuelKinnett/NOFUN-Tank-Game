#include <math.h>
#include "../include/Tank.hpp"

//static constants
const double Tank::PI = 3.14159265358979323846;
const double Tank::DEG_TO_RAD = PI / 180;
const double Tank::RAD_TO_DEG = 180 / PI;
const double Tank::M_TO_PX = 50 / 6.75;
const double Tank::KPH_TO_PXS = 1 / 3.6*M_TO_PX;

Tank::Tank() : Tank(52.0, 42.0, 18000.0, 400.0, 64.4, 100.0) {}

Tank::Tank(double hullTraverseRate, double turretTraverseRate, double weight, double horsepower, double maxVel, double brakeForce)
{
    this->hullTraverseRate = hullTraverseRate * DEG_TO_RAD;
    this->horsepower = horsepower;
    this->weight = weight;
    this->brakeForce = brakeForce;
    this->maxVel = maxVel * KPH_TO_PXS;
    this->turretTraverseRate = turretTraverseRate * DEG_TO_RAD;

    moveState = orienter(0);
    hullRotation = 0;

    positionX = positionY = 0;
    hp = maxHP = 1000;
    moving = false;

    velocity = 0;

    tankX[0] = -3.32 / 2 * M_TO_PX; tankX[1] = 3.32 / 2 * M_TO_PX; tankX[2] = 3.32 / 2 * M_TO_PX; tankX[3] = -3.32 / 2 * M_TO_PX;
    tankY[0] = -6.75 / 2 * M_TO_PX; tankY[1] = -6.75 / 2 * M_TO_PX; tankY[2] = 6.75 / 2 * M_TO_PX; tankY[3] = 6.75 / 2 * M_TO_PX;

    turretVertX[0] = -0.8 / 2 * M_TO_PX; turretVertX[1] = -turretVertX[0]; turretVertX[2] = turretVertX[1]; turretVertX[3] = turretVertX[0];
    turretVertY[0] = 0; turretVertY[1] = 0; turretVertY[2] = 7 * M_TO_PX; turretVertY[3] = 7 * M_TO_PX;
}

void Tank::setAcc(double deltaTime)
{
    //TODO: calculate acceleration based on
    //horsepower, velocity, weight, gear ratio, rpm, ground resistance, ground grip, torque, ...
    acceleration = (1000*horsepower / weight) * deltaTime;
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
void Tank::turretRotate(double angle)
{
    moveState = orienter(moveState | orienter::tRot);
    turretAngleTarget = angle;
}
void Tank::turretRotateTo(double angle)
{
    moveState = orienter(moveState | orienter::tRot);
    turretAngleTarget = fmod(angle - turretRot, 2 * PI);
}

void Tank::target(const MultiplayerObject& t)
{
    double cx = t.getPosX() - positionX;
    double cy = t.getPosY() - positionY;
    double c = cos(turretRot + hullRotation);
    double s = sin(turretRot + hullRotation);
    double x = -cx * c - cy * s;
    double y = cy * c - cx * s;
    double angle = atan2(x, y);
    turretRotate(angle);
}

void Tank::interpolate(double deltaTime)
{
    moveState = lastMoveState;
    update(deltaTime);
}

void Tank::setPos(double x, double y)
{
    positionX = x;
    positionY = y;
}
void Tank::setRot(double angle)
{
    hullRotation = angle;
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
        velocity *= pow(brakeForce, -deltaTime);
    }
    else if(moveState & fwd) //forward
    {
        moving = true;
        velocity += acceleration;
        if(velocity > maxVel)
        {
            velocity = maxVel;
        }
    }
    else if(moveState & bwd) //backward, only allow one motion
    {
        moving = true;
        velocity -= acceleration;
        if(velocity < -maxVel/4)
        {
            velocity = -maxVel/4;
        }
    }
    else //stationary
    {
        moving = false;
        velocity *= pow(1.95, -deltaTime);
    }
    if(moveState & right) //turn right
    {
        hullRotation += hullTraverseRate * deltaTime;
        hullRotation = fmod(hullRotation, 2*PI);
    }
    if(moveState & left) //turn left
    {
        hullRotation -= hullTraverseRate * deltaTime;
        hullRotation = fmod(hullRotation, 2*PI);
    }
    if (moveState & tRot) {
        double turretRemain = turretAngleTarget;

        if(turretRemain > turretTraverseRate*deltaTime)
        {
            turretRot += turretTraverseRate * deltaTime;
        }
        else if(-turretRemain > turretTraverseRate*deltaTime)
        {
            turretRot -= turretTraverseRate * deltaTime;
        }
        else
        {
            turretRot += turretRemain;
        }
        fmod(turretRot, 2*PI);
    }

    //Move the tank
    positionX += -sin(hullRotation) * velocity * deltaTime;
    positionY += cos(hullRotation) * velocity * deltaTime;
    lastMoveState = moveState;
    moveState = orienter(0); //reset moveState to contain bits set
}

void Tank::draw()
{
    glPushMatrix();
    glTranslatef(positionX, positionY, 0.0f);
    glRotatef(hullRotation * RAD_TO_DEG, 0.0f, 0.0f, 1.0f);

    glBegin(GL_QUADS);
    {
        for(int i = 0; i < 4; i++)
        {
            glVertex2d(tankX[i], tankY[i]);
        }
    }
    glEnd();

    glRotatef(turretRot * RAD_TO_DEG, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    {
        for(int i = 0; i < 4; i++)
        {
            glVertex2d(turretVertX[i], turretVertY[i]);
        }
    }
    glEnd();
    glPopMatrix();
}

void Tank::processKeys(GLFWwindow* window, double cursorX, double cursorY)
{
    cursorX -= positionX;
    cursorY -= positionY;

    double c = cos(turretRot+hullRotation);
    double s = sin(turretRot+hullRotation);
    double x = -cursorX * c - cursorY * s;
    double y = cursorY * c - cursorX * s;
    double angle = atan2(x, y); //swap x & y for correct angle because turret is pointing upwards
    turretRotate(angle);

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
/*
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
*/
