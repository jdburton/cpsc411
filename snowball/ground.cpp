
#include "ground.h"
#include <GL/glut.h>

extern int list_number;

Ground::Ground() : Object(0.0,-0.4,0.0){


	mat = new Material(1.0,1.0,1.0,1.0,1.0,1.0,2.0);
	

}



Ground::~Ground(){
}

void Ground::draw(){

	glPushMatrix();
	

	glTranslatef(center_point.x,center_point.y,center_point.z);
  glRotatef(-90.0,1.0,0.0,0.0);
  glNewList(++list_number,GL_COMPILE);

  mat->set();

	GLUquadricObj * qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluDisk(qobj,0.0,25.0,10,10);

	glEndList();
	glPopMatrix();

	list_index = list_number;
	

}

void Ground::refresh(){

  glPushMatrix();
	glTranslatef(center_point.x,center_point.y,center_point.z);
  glRotatef(-90.0,1.0,0.0,0.0);
  
	glCallList(list_index);
	glPopMatrix();
	

}

