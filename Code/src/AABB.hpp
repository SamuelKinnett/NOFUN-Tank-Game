#ifndef AABB_HPP_INCLUDED_
#define AABB_HPP_INCLUDED_

//A class describing an axis aligned bounding box
class AABB
{
	int min[2];	//Top left corner
	int max[2];	//Bottom right corner

	public:
		bool CheckCollision(AABB);
		void MoveBB(float, float);
};

#endif
