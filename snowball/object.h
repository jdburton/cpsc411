
#ifndef OBJECT_H
#define OBJECT_H

//a very important definition

struct point{

float x;
float y;
float z;

};

//base class for objects

class Object {

protected:

		struct point center_point;
		int list_index;
	

public: 
	int is_dead;

	Object();
	Object(float x, float y, float z);
	virtual void draw();
	 virtual void refresh();
	 virtual void move();
  	int isDead();
	
	~Object();
	
	friend class ObjectManager;
};

#endif
