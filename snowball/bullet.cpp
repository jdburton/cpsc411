
#include "bullet.h"
#include "Timer.h"


#include <math.h>
#include <GL/glut.h>


extern Timer timer;				//to keep time of bullet
extern int list_number;

Bullet::Bullet() : Object(){
	start_point.x = 0.0;
	start_point.y = 0.0;
	start_point.z = 0.0;

	velocity.x = 0.0;
	velocity.y = 0.0;
	velocity.z = 0.0;
	
	last_position.x = 0.0;
	last_position.y = 0.0;
	last_position.z = 0.0;
	



	is_dead = 1;


}

Bullet::Bullet(float sx, float sy, float sz, float dx, float dy, float dz, float speed) : Object(sx,sy,sz) {


			start_point.x = sx;
			start_point.y = sy;
			start_point.z = sz;
			
			
			last_position.x = sx;
			last_position.y = sy;
			last_position.z = sz;


			float length = sqrt(dx*dx+dy*dy+dz*dz);				//get the length of the direction vector

			velocity.x = speed * dx / length;							//divide by length to get unit vector, then multiply by speed to find velocity
		        velocity.y = speed * dy / length;
			velocity.z = speed * dz / length;

			mat_black = new Material(0.5,0.5,1.0,1.0,1.0,2.0);

			start_time = timer.time()/1000.0;				//time started in seconds
			last_move = timer.time();

			stopped = 0;

}

Bullet::Bullet(const struct point & s, const struct point & d, float speed) : Object(s.x,s.y,s.z) {

			start_point.x = s.x;
			start_point.y = s.y;
			start_point.z = s.z;

			last_position.x = s.x;
			last_position.y = s.y;
			last_position.z = s.z;


			float length = sqrt(d.x*d.x+d.y*d.y+d.z*d.z);				//get the length of the direction vector

			velocity.x = speed * (d.x / length);							//divide by length to get unit vector, then multiply by speed to find velocity
     			velocity.y = speed * (d.y / length);
			velocity.z = speed * (d.z / length);

    			mat_black = new Material(1.0,1.0,1.0,0.2,0.2,0.2);
			start_time = timer.time()/1000.0;				//time started in seconds
			last_move = timer.time();

			stopped = 0;
			is_dead = 0;
		

}


Bullet::~Bullet(){

	delete mat_black;

}

void Bullet::draw(){

	if(is_dead) return;

	glPushMatrix();
	glTranslatef(center_point.x,center_point.y,center_point.z);
  mat_black->set();
		
  glNewList(++list_number,GL_COMPILE);
  glutSolidSphere(0.02, 10, 10);
	glEndList();
	glPopMatrix();	

	glFlush();

	list_index = list_number;


}

void Bullet::refresh(){

  if(is_dead) return;

  glPushMatrix();
  glTranslatef(center_point.x,center_point.y,center_point.z);
  mat_black->set();
	

  glutSolidSphere(0.02, 10, 10);
  glPopMatrix();

}

void Bullet::move(){


if(stopped) return;

    float t = timer.time()/1000.0 - start_time;     //time in seconds
    
    
    		last_position.x = center_point.x;
    		last_position.y = center_point.y;
    		last_position.z = center_point.z;
    
    

		center_point.x = velocity.x * t + start_point.x;
		center_point.y = 0.5*ACC*t*t+velocity.y*t + start_point.y;
		center_point.z = velocity.z * t + start_point.z;

		if(center_point.y < -0.4){ stopped = 1; center_point.y = -0.4;}

		last_move = timer.time();
		

}


		
