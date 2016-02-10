
#include "object.h"

Object::Object(){

	is_dead = 1;

}

Object::Object(float x, float y, float z){
	
    center_point.x = x;
		center_point.y = y;
		center_point.z = z;
		
		is_dead = 0;

}


int Object::isDead(){

	return is_dead;

}


Object::~Object(){
}

void Object::move(){
}

void Object::refresh(){
}

void Object::draw(){

}


