#include <math.h>
#include "../include/tank.h"

Tank::Tank()
{
    moveState = orienter(0);
    hullRotation = 0;
    hullTraverseRate = 90 * DEG_TO_RAD;
    positionX = positionY = 0;
    hp = maxHP = 1000;
    moving = false;
    horsepower = 5000;
    brakeForce = 100;
    weight = 22;
    velocity = 0;
    maxVel = 100 * KPH_TO_PXS;
    tankX[0] = -3.32/2*M_TO_PX; tankX[1] = 3.32/2*M_TO_PX; tankX[2] = 3.32/2*M_TO_PX; tankX[3] = -3.32/2*M_TO_PX;
    tankY[0] = -6.75/2*M_TO_PX; tankY[1] =  -6.75/2*M_TO_PX; tankY[2] = 6.75/2*M_TO_PX; tankY[3] = 6.75/2*M_TO_PX;

    gun_vertX[0] = -0.8/2*M_TO_PX; gun_vertX[1] = -gun_vertX[0]; gun_vertX[2] = gun_vertX[1]; gun_vertX[3] = gun_vertX[0];
    gun_vertY[0] = 0; gun_vertY[1] = 0; gun_vertY[2] = 7*M_TO_PX; gun_vertY[3] = 7*M_TO_PX;

    gun_traverse = 90*DEG_TO_RAD;
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
void Tank::gunLeft() {
    moveState = orienter(moveState | orienter::gun_left);
}
void Tank::gunRight() {
    moveState = orienter(moveState | orienter::gun_right);
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
            velocity = maxVel;
    }
    else if(moveState & bwd) //backward, only allow one motion
    {
        moving = true;
        velocity -= acceleration;
        if(velocity < -maxVel/4)
            velocity = -maxVel/4;
    }
    else //stationary
    {
        moving = false;
        velocity *= pow(1.95, -deltaTime);
    }
    if(moveState & right) //turn right
    {
        hullRotation += hullTraverseRate * deltaTime;
        while(hullRotation > 2*PI)
            hullRotation -= 2*PI;
    }
    if(moveState & left) //turn left
    {
        hullRotation -= hullTraverseRate * deltaTime;
        while(hullRotation < 0)
            hullRotation += 2*PI;
    }
    if(moveState & gun_right) {
        gun_rot += gun_traverse * deltaTime;
        while(gun_rot > 2*PI)
            gun_rot -= 2*PI;
    }
    if(moveState & gun_left) {
        gun_rot -= gun_traverse * deltaTime;
        while(gun_rot < 0)
            gun_rot += 2*PI;
    }

    //Move the tank
    positionX += -sin(hullRotation) * velocity * deltaTime;
    positionY += cos(hullRotation) * velocity * deltaTime;
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

    glRotatef(gun_rot * RAD_TO_DEG, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    {
        for(int i = 0; i < 4; i++)
        {
            glVertex2d(gun_vertX[i], gun_vertY[i]);
        }
    }
    glEnd();
    glPopMatrix();
}

void Tank::processKeys(GLFWwindow* window)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    xpos -= positionX;
    ypos -= positionY;

    double c = cos(gun_rot+hullRotation);
    double s = sin(gun_rot+hullRotation);
    double x = -(xpos * c + ypos * s);
    //double y = ypos * c - xpos * s;
    if(x < 0)
        gunLeft();
    else if(x > 0) {
        gunRight();
    }

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
