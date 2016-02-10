/***************************************************************************
                          target.h  -  description

Creates a target for the snowball game;


 ***************************************************************************/


#ifndef TARGET_H
#define TARGET_H

#include "transparentmaterial.h"
#include "object.h"



class Target : public Object{

private:
		
		Material * mat;			//outer material
		Material * mat2;		//outer material
		TransparentMaterial * hit_mat;	//material when hit

		float radius;

		struct point velocity;		//velocity of target
		
		int last_time;			//last time it moved
		int is_hit;			//has the target been hit

		int delay_time;			//delay between movements
		void ai();			//move (somewhat) intelligently
public: 
	Target();
	Target(float x, float y, float z, float vx = 0.0, float vy = 0.0, float vz = 0.0);
	~Target();
 	void draw();
	void refresh();
	int hit();
	void move(); 						//move incrementally

	friend class ObjectManager;
};

#endif
