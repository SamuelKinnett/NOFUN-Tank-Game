#include <math.h>
#include "Tank.hpp"

//static constants
const double Tank::PI = 3.14159265358979323846;
const double Tank::DEG_TO_RAD = PI / 180;
const double Tank::RAD_TO_DEG = 180 / PI;
const double Tank::M_TO_PX = 50 / 6.75;
const double Tank::KPH_TO_PXS = 1 / 3.6*M_TO_PX;

Tank::Tank() : Tank(52.0, 42.0, 18000.0, 400.0, 64.4, 100.0) {}

Tank::Tank(double hullTraverseRate, double turretTraverseRate, double weight, double horsepower, double maxVel, double brakeForce)
{
    this->_hullTraverseRate = hullTraverseRate * DEG_TO_RAD;
    this->_horsepower = horsepower;
    this->_weight = weight;
    this->_brakeForce = brakeForce;
    this->_maxVel = maxVel * KPH_TO_PXS;
    this->_turretTraverseRate = turretTraverseRate * DEG_TO_RAD;

    _moveState = orienter(0);
    _hullRotation = 0;

    _positionX = _positionY = 0;
    _hp = _maxHP = 1000;
    _moving = false;

    _velocity = 0;

    _tankX[0] = -3.32 / 2 * M_TO_PX; _tankX[1] = 3.32 / 2 * M_TO_PX; _tankX[2] = 3.32 / 2 * M_TO_PX; _tankX[3] = -3.32 / 2 * M_TO_PX;
    _tankY[0] = -6.75 / 2 * M_TO_PX; _tankY[1] = -6.75 / 2 * M_TO_PX; _tankY[2] = 6.75 / 2 * M_TO_PX; _tankY[3] = 6.75 / 2 * M_TO_PX;

    _turretVertX[0] = -0.8 / 2 * M_TO_PX; _turretVertX[1] = -_turretVertX[0]; _turretVertX[2] = _turretVertX[1]; _turretVertX[3] = _turretVertX[0];
    _turretVertY[0] = 0; _turretVertY[1] = 0; _turretVertY[2] = 7 * M_TO_PX; _turretVertY[3] = 7 * M_TO_PX;
}

void Tank::setAcc(double deltaTime)
{
    //TODO: calculate acceleration based on
    //horsepower, velocity, weight, gear ratio, rpm, ground resistance, ground grip, torque, ...
    _acceleration = (1000*_horsepower / _weight) * deltaTime;
}

void Tank::moveFwd()
{
    _moveState = orienter(_moveState | orienter::FWD);
}
void Tank::moveBwd()
{
    _moveState = orienter(_moveState | orienter::BWD);
}
void Tank::moveBrk()
{
    _moveState = orienter(_moveState | orienter::BRAKE);
}
void Tank::traverseLeft()
{
    _moveState = orienter(_moveState | orienter::LEFT);
}
void Tank::traverseRight()
{
    _moveState = orienter(_moveState | orienter::RIGHT);
}
void Tank::turretRotate(double angle)
{
    _moveState = orienter(_moveState | orienter::T_ROT);
    _turretAngleTarget = angle;
}
void Tank::turretRotateTo(double angle)
{
    _moveState = orienter(_moveState | orienter::T_ROT);
    _turretAngleTarget = fmod(angle - _turretRot, 2 * PI);
}

void Tank::target(const MultiplayerObject& t)
{
    double cx = t.getPosX() - _positionX;
    double cy = t.getPosY() - _positionY;
    double c = cos(_turretRot + _hullRotation);
    double s = sin(_turretRot + _hullRotation);
    double x = -cx * c - cy * s;
    double y = cy * c - cx * s;
    double angle = atan2(x, y);
    turretRotate(angle);
}

void Tank::interpolate(double deltaTime)
{
    _moveState = _lastMoveState;
    update(deltaTime);
}

void Tank::setPos(double x, double y)
{
    _positionX = x;
    _positionY = y;
}
void Tank::setRot(double angle)
{
    _hullRotation = angle;
}

//This method should be called every time the main update loop runs and updates
//the tank's variables
//deltaTime is used to make a simple Euler Integrator to ensure framerate
//independent movement.
void Tank::update(double deltaTime)
{
    //sets acceleration based on various parameters
    setAcc(deltaTime);
    if(_moveState & BRAKE)
    {
        _moving = false;
        _velocity *= pow(_brakeForce, -deltaTime);
    }
    else if(_moveState & FWD) //forward
    {
        _moving = true;
        _velocity += _acceleration;
        if(_velocity > _maxVel)
        {
            _velocity = _maxVel;
        }
    }
    else if(_moveState & BWD) //backward, only allow one motion
    {
        _moving = true;
        _velocity -= _acceleration;
        if(_velocity < -_maxVel/4)
        {
            _velocity = -_maxVel/4;
        }
    }
    else //stationary
    {
        _moving = false;
        _velocity *= pow(1.95, -deltaTime);
    }
    if(_moveState & RIGHT) //turn right
    {
        _hullRotation += _hullTraverseRate * deltaTime;
        _hullRotation = fmod(_hullRotation, 2*PI);
    }
    if(_moveState & LEFT) //turn left
    {
        _hullRotation -= _hullTraverseRate * deltaTime;
        _hullRotation = fmod(_hullRotation, 2*PI);
    }
    if (_moveState & T_ROT) {
        double turretRemain = _turretAngleTarget;

        if(turretRemain > _turretTraverseRate * deltaTime)
        {
            _turretRot += _turretTraverseRate * deltaTime;
        }
        else if(-turretRemain > _turretTraverseRate*deltaTime)
        {
            _turretRot -= _turretTraverseRate * deltaTime;
        }
        else
        {
            _turretRot += turretRemain;
        }
        fmod(_turretRot, 2*PI);
    }

    //Move the tank
    _positionX += -sin(_hullRotation) * _velocity * deltaTime;
    _positionY += cos(_hullRotation) * _velocity * deltaTime;
    _lastMoveState = _moveState;
    _moveState = orienter(0); //reset _moveState to contain bits set
}

void Tank::draw()
{
    glPushMatrix();
    glTranslatef(_positionX, _positionY, 0.0f);
    glRotatef(_hullRotation * RAD_TO_DEG, 0.0f, 0.0f, 1.0f);

    glBegin(GL_QUADS);
    {
        for(int i = 0; i < 4; i++)
        {
            glVertex2d(_tankX[i], _tankY[i]);
        }
    }
    glEnd();

    glRotatef(_turretRot * RAD_TO_DEG, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    {
        for(int i = 0; i < 4; i++)
        {
            glVertex2d(_turretVertX[i], _turretVertY[i]);
        }
    }
    glEnd();
    glPopMatrix();
}

void Tank::processKeys(GLFWwindow* window, double cursorX, double cursorY)
{
    cursorX -= _positionX;
    cursorY -= _positionY;

    double c = cos(_turretRot+_hullRotation);
    double s = sin(_turretRot+_hullRotation);
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
