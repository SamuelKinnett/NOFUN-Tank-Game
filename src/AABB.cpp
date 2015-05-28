#include "AABB.h"

//This method checks to see if the passed bounding box will collide with this
bool AABB::CheckCollision(AABB otherBox)
{
	if (max[0] < otherBox.min[0] ||
                max[1] < otherBox.min[1] ||
                max[0] > otherBox.max[0] ||
                min[1] > otherBox.max[1])
            {
                return false;
            }
    return true;
}

//This method moves the bounding box by the passed ammount
void AABB::MoveBB(float xDisplacement, float yDisplacement)
{
	max[0] += xDisplacement;
	max[1] += yDisplacement;
	min[0] += xDisplacement;
	min[1] += yDisplacement;
}
