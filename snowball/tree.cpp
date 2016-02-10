/***************************************************************************
                          tree.cpp  -  description
                             -------------------
    begin                : Tue Dec 4 2001
    copyright            : (C) 2001 by James Burton
    email                : jdburto@clemson.edu
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "tree.h"
#include "random.h"
#include <GL/glut.h>
//#include <stdlib.h>

CRandom rando;

extern int list_number;

Tree::Tree(){
}

Tree::Tree(float x, float y, float z) : Object(x,y,z) {

		

		leaves = new Material(0.1,0.45,0.2,0.0,0.0,0.0,25.0);
		trunk =  new Material(0.2,0.0,0.0,0.0,0.0,0.0,25.0);



}

Tree::~Tree(){
}

void Tree::draw(){


			
			glPushMatrix();
		  //trunk
 			glNewList(++list_number,GL_COMPILE);

      glTranslatef(center_point.x,center_point.y,center_point.z);
      trunk->set();
			 glutSolidCube(0.5);

    	glEndList();
			glPopMatrix();

			list_index = list_number;

      //cone
			glPushMatrix();
      glNewList(++list_number,GL_COMPILE);
      leaves->set();
			glTranslatef(center_point.x,center_point.y+0.05,center_point.z);
      glRotatef(-90.0, 1.0, 0.0, 0.0);
      glutSolidCone(rando.number(5,15)/10.0, rando.number(10,30)/10.0, 50, 50);
 			glEndList();
      glPopMatrix();

}


void Tree::refresh(){

		glPushMatrix();
		glCallList(list_index);
		glPopMatrix();
		glPushMatrix();
		glCallList(list_index+1);
		glPopMatrix();

}



