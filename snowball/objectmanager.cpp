/***************************************************************************
                          objectmanager.cpp  -  description
                             -------------------
    begin                : Wed Dec 5 2001
    copyright            : (C) 2001 by James Burton
    email                : jdburto@clemson.edu
 ***************************************************************************/


#include "objectmanager.h"
#include "bullet.h"
#include "target.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>

const float BULLET_SPEED = 10.0;
const int NUMBER_OBJECTS = 32;

extern int current_level;

ObjectManager::ObjectManager(){

		ObjectList = new Object*[NUMBER_OBJECTS];
		
	 	size = 0;

		current_bullet = 0;

		int i;
		
		
		for(i = 0; i < NUM_BULLETS; i++){
		
			create_bullet();
		
		
		}
		
		for(i = NUM_BULLETS; i<NUMBER_OBJECTS; i++){
     	
				ObjectList[i] = new Object;

		}
		number_targets = 0;
		total_score = 0;




}

void ObjectManager::create_target(float x, float y, float z){


	if(size >= NUMBER_OBJECTS) return;

		ObjectList[size] = new Target(x,y,z);
		ObjectList[size]->draw();

		size++;
		number_targets++;


					
}

void ObjectManager::create_bullet(){

	if(size >= NUMBER_OBJECTS) return;


		ObjectList[size] = new Bullet;
		
		size++;
	
}

void ObjectManager::fire(const struct point & s, const struct point & d){

		total_score -=1;

		
		ObjectList[current_bullet] = new Bullet(s,d,BULLET_SPEED);
		
		ObjectList[current_bullet]->draw();
		
		current_bullet = (current_bullet +1)  % NUM_BULLETS;



}

void ObjectManager::animate(){
	int i;

	for(i = 0; i < size; i++){
		if(!(ObjectList[i]->isDead())){
			ObjectList[i]->move();
			ObjectList[i]->refresh();
			
		}
	


	}


}


void ObjectManager::collision_detection(){

   struct point bullet_dir;
   struct point hit_point;

 
   for(int i = 0; i < NUM_BULLETS; i++){
      for(int j = NUM_BULLETS; j < size; j++){
      
      	if(((static_cast<Bullet*>(ObjectList[i])->last_position.z <= ObjectList[j]->center_point.z) ^ (ObjectList[i]->center_point.z <= ObjectList[j]->center_point.z)) && (static_cast<Bullet*>(ObjectList[i])->is_dead == 0) && (static_cast<Bullet*>(ObjectList[i])->stopped == 0)){
      	
      		bullet_dir.x = ObjectList[i]->center_point.x  - static_cast<Bullet*>(ObjectList[i])->last_position.x;
      		bullet_dir.y = ObjectList[i]->center_point.y  - static_cast<Bullet*>(ObjectList[i])->last_position.y;
      		bullet_dir.z = ObjectList[i]->center_point.z  - static_cast<Bullet*>(ObjectList[i])->last_position.z;
      
      		float pct = (ObjectList[j]->center_point.z - static_cast<Bullet*>(ObjectList[i])->last_position.z)/(ObjectList[i]->center_point.z - static_cast<Bullet*>(ObjectList[i])->last_position.z);
 		hit_point.x = ObjectList[i]->center_point.x - (1.0-pct) * bullet_dir.x;
 		hit_point.y = ObjectList[i]->center_point.y - (1.0-pct) * bullet_dir.y;
 		hit_point.z = ObjectList[i]->center_point.z - (1.0-pct) * bullet_dir.z;
 		
 		
 		
 		float dist = distance(hit_point,ObjectList[j]->center_point);
 		
 		if(dist < 0.3){		//if you hit the target
 		
 			if(static_cast<Target*>(ObjectList[j])->hit()){
 			add_to_score(dist);
			number_targets--;
			}
			
 		}//end if dist < 3.0
     	 
      }//end if z
   }//next j
		
 }//next i


}


float ObjectManager::distance(const struct point & bullet, const struct point & target){

 return	sqrt((bullet.x-target.x)*(bullet.x-target.x)+(bullet.y-target.y)*(bullet.y-target.y));//+(bullet.z-target.z)*(bullet.z-target.z));


}


ObjectManager::~ObjectManager(){

	for(int i = 0; i < size; i++)
		delete ObjectList[i];
		
		delete[] ObjectList;

}

void ObjectManager::draw_text(){

	int x = 0;
	int y = 0;
	
	 char * string = new char[64];
	 sprintf(string,"Level: %d    Score: %d    Targets Remaining %d",current_level+1,total_score,number_targets);
	 
	 
    int win_width, win_height;

    win_width = 720;
    win_height = 720;

    glPushAttrib(GL_ENABLE_BIT | GL_TRANSFORM_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, win_width, 0, win_height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef((float)x, (float)y, 0.0);
    
    glColor3f(0.0,0.0,0.0);

    glRasterPos2f(0.0,0.0);
    while (*string != '\0') {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *string++);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
    glFlush();
}


void ObjectManager::add_to_score(float dist){


	int temp = static_cast<int>((0.4-dist)*10 *1000);
	
		
	total_score+=temp;
	
}

int ObjectManager::is_cleared(){

	return (number_targets == 0)? 1:0;

}

void ObjectManager::reset(){


		
	 size = NUM_BULLETS;

	current_bullet = 0;

	int i;
		
	for(i = NUM_BULLETS; i<NUMBER_OBJECTS; i++){
     	
		ObjectList[i] = new Object;

	}
	number_targets = 0;
	
}
