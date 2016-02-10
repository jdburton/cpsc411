#include "target.h"
#include "Timer.h"
#include "random.h"

#include <GL/glut.h>
#include <iostream>

extern int list_number;

extern Timer timer;
extern CRandom rando;


Target::Target(){
	

}

Target::Target(float x, float y, float z, float vx, float vy, float vz) : Object(x,y,z) {

		mat = new Material(1.0,0.0,0.0,0.0,0.0,0.0,25.0);
		mat2 = new Material(1.0,1.0,1.0,0.0,0.0,0.0,25.0);		
		hit_mat = new TransparentMaterial(0.0,0.0,0.5,0.4,0.0,0.0,0.0,0.4,25.0);

		radius = 0.3;

		is_dead = 0;
		is_hit = 0;
		
		velocity.x = vx;
		velocity.y = vy;
		velocity.z = vz;
		
		
		last_time = timer.time();
		delay_time = 0;
		

}

Target::~Target(){

	delete mat;
}


void Target::draw(){



	glPushMatrix();
	glTranslatef(center_point.x,center_point.y,center_point.z);
	glNewList(++list_number,GL_COMPILE);
	mat->set();
	GLUquadricObj * qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluDisk(qobj,0.2,radius,12,6);
	mat2->set();
	gluDisk(qobj,0.1,0.2,12,6);
	mat->set();
	gluDisk(qobj,0.0,0.1,12,6);
	


  glEndList();	
  glPopMatrix();

	list_index = list_number;

	
}

void Target::refresh(){

  glPushMatrix();
  glTranslatef(center_point.x,center_point.y,center_point.z);
  glCallList(list_index);
  glPopMatrix();



}



void Target::move(){

	if(is_hit) return;

	float temp = (timer.time()-last_time)/1000.0;
	
	center_point.x += velocity.x * temp;//(timer.time()-last_time)/1000.0;	
	center_point.y += velocity.y * temp;//(timer.time()-last_time)/1000.0;	
	center_point.z += velocity.z * temp;//(timer.time()-last_time)/1000.0;	
	
	
	
	ai();
	
	
	
}


void Target::ai(){

if(!timer.elapsed(last_time,delay_time)) return;
	
		if(center_point.x < -15.0)
			velocity.x = rando.number(0,50)/1000.0;
		else if(center_point.x > 15.0)
			velocity.x = rando.number(-50,0)/1000.0;
		else
			velocity.x = rando.number(-50,50)/1000.0;

		if(center_point.y < 0.0)
			velocity.y = rando.number(0,50)/1000.0;
		else if(center_point.y > 3.0)
			velocity.y = rando.number(-50,0)/1000.0;
		else
			velocity.y = rando.number(-50,50)/1000.0;

		if(center_point.z < -20.0)
			velocity.z = rando.number(0,50)/1000.0;
		else if(center_point.z > 5.0)
			velocity.z = rando.number(-50,0)/1000.0;
		else
			velocity.z = rando.number(-50,50)/1000.0;
	
	
	
	delay_time = 1500 + rando.number(0,2500);
	
	last_time = timer.time();


}

int Target::hit(){

	if(is_hit) return 0;

 	glPushMatrix();
	

	glTranslatef(center_point.x,center_point.y,center_point.z);

  	glNewList(++list_number,GL_COMPILE);
  	hit_mat->set();
  	
  	glEnable(GL_BLEND);
  	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	GLUquadricObj * qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluDisk(qobj,0.0,radius,12,6);
	

	glDisable(GL_BLEND);
	glEndList();	
	glPopMatrix();

	is_hit = 1;
	list_index = list_number;

	return 1;

}
