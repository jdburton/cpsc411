/***************************************************************************
                          objectmanager.h  -  description
                             -------------------
    begin                : Wed Dec 5 2001
    copyright            : (C) 2001 by James Burton
    email                : jdburto@clemson.edu
 ***************************************************************************/

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H



#include "object.h"



const int NUM_BULLETS = 10;

class ObjectManager {

private:

	 Object ** ObjectList;	//list of object

	int size;		//size of list
	int target_index;	//index of the first target
	int current_bullet;	//current bullet being fired
	float distance(const struct point & bullet, const struct point & target);  //distance between two points (x,y)
	void add_to_score(float dist);  
	int total_score;	
	int number_targets;
	void create_bullet();	//create a new bullet


public:
	ObjectManager();
	~ObjectManager();

	void animate();		//animate targets and bullets
	void fire(const struct point & s, const struct point & d);	//throw a snowball
	void create_target(float x, float y, float z);	//create a new target
	void draw_text();	//draw the text string
	
	void collision_detection();	//detect the collisions
	void reset();			//reset the objects
	int is_cleared();		//has the level been cleared
	
  

};

#endif
