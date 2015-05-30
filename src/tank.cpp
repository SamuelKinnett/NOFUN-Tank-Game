#include <math.h>
#include "tank.h"

#define RIGHT 1
#define LEFT 0
#define FORWARDS 2
#define BACKWARDS 1
#define STATIONARY 0
#define FRONT 0
#define SIDES 1
#define REAR 2
#define DEGREES_TO_RADIANS 0.0174532925f

//This method handles moving the tank, given a direction
//2 = forwards, 1 = backwards, 0 = no input.
//deltaTime is used to make a simple Euler Integrator to ensure framerate
//independent acceleration.
void Tank::Move(int direction, float deltaTime)
{
   float acceleration = (horsepower / weight) / 10;
   acceleration *= deltaTime;
   //Placeholder equation, recalculating it every time allows for engine damage
   //and horsepower loss to be reflected in speed
   float reversingSpeed = ((topSpeed * -1) / 4);
   //reversing speed is currently one quarter of the normal top speed
   switch (direction)
   {
      case (FORWARDS):

         moving = true;
         if (currentSpeed + acceleration < topSpeed)
            currentSpeed += acceleration;
         else
            currentSpeed = topSpeed;
         break;

      case (BACKWARDS):

         moving = true;
         if (currentSpeed - acceleration > reversingSpeed)
            currentSpeed -= acceleration;
         else
            currentSpeed = reversingSpeed;
         break;

      case (STATIONARY):

         moving = false;
         break;
   }

}

//This method handles traversing the tank, given a direction
//1 = right, 0 = left
void Tank::Traverse(int direction)
{
   switch (direction)
   {
      case (RIGHT):

         if (hullFacing + hullTraverseRate < (360 * DEGREES_TO_RADIANS))
            hullFacing += hullTraverseRate;
         else
            hullFacing = (hullFacing + hullTraverseRate) -
                           (360 * DEGREES_TO_RADIANS);
         break;

      case (LEFT):

         if (hullFacing - hullTraverseRate > 0)
            hullFacing -= hullTraverseRate;
         else
            hullFacing = (hullFacing - hullTraverseRate) +
                           (360 * DEGREES_TO_RADIANS);

         break;
   }
}

//This method should be called every time the main update loop runs and updates
//the tank's variables
//deltaTime is used to make a simple Euler Integrator to ensure framerate
//independent movement.
void Tank::Update(float deltaTime)
{
   float acceleration = (horsepower / weight) / 10;
   //Check to see if the tank needs to decelerate
   if (!moving && currentSpeed > 0) {
      //Decelerate
      if (currentSpeed - (acceleration * 10) > 0)
         currentSpeed -= (acceleration * 10);
      else
         currentSpeed = 0;
   }

   //Move the tank
   positionX += (sin (hullFacing * DEGREES_TO_RADIANS) * currentSpeed)
                  *deltaTime;
   positionY += (cos (hullFacing * DEGREES_TO_RADIANS) * currentSpeed)
                  *deltaTime;
}

//This method handles traversing the turret, given a direction
//1 = right, 0 = left
void Tank::RotateTurret(int direction)
{
   switch (direction)
   {
      case (RIGHT):

         if (turretFacing + turretTraverseRate < (360 * DEGREES_TO_RADIANS))
            turretFacing += turretTraverseRate;
         else
            turretFacing = (turretFacing + turretTraverseRate) -
                           (360 * DEGREES_TO_RADIANS);
         break;

      case (LEFT):

         if (turretFacing - turretTraverseRate > 0)
            turretFacing -= turretTraverseRate;
         else
            turretFacing = (turretFacing - turretTraverseRate) +
                           (360 * DEGREES_TO_RADIANS);

         break;
   }
}

//This method handles the tank being hit by an enemy shot
//angleOfShot is the angle of the enemy shell and is given in radians.
//damage and penetration are, obviously, the damage and penetration of the
//enemy shot.
//areaHit details the area of the tank that was hit. 0 = front, 1 = sides,
//2 = rear.
void Tank::Hit(float angleOfShot, int damage, int penetration, int areaHit)
{
   //TODO: Everything here, currently in progress
}
