//A class describing an axis aligned bounding box

//==============================================================================
//Include guard
#ifndef __AABB_INCLUDED__
#define __AABB_INCLUDED__
//==============================================================================
//Class definition

class AABB {
	int min[2];	//Top left corner
	int max[2];	//Bottom right corner

	public:
		bool CheckCollision(AABB);
		void MoveBB(float, float);
}

#endif
