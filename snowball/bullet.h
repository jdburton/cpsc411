
#ifndef BULLET_H
#define BULLET_H

#include "object.h"
#include "material.h"


const int ACC = -4.0;		//acceleration

class Bullet : public Object  {

	private:

		struct point velocity;			//vector with x, y, z velocity

		struct point start_point;
		struct point last_position;

		Material * mat_black;

		int last_move;					//time of last move;
		float start_time;

		int stopped;
		

		


public: 
	Bullet();
	Bullet(float sx, float sy, float sz, float dx, float dy, float dz, float speed = 1.0);
	Bullet(const struct point & s, const struct point & d, float speed = 1.0);
	void draw();
	void refresh();
	void move();

	~Bullet();
	
	friend class ObjectManager;

		



};

#endif
