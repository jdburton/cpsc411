#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H



#include "object.h"



enum ObjectType{GROUND_OBJECT,TREE_OBJECT,HILL_OBJECT};

class SceneManager {

private:

	 Object ** SceneList;	//List of scenery

	int size;		//size of list

public:
	SceneManager();
	~SceneManager();

	void display_scene();	//display the scene
	void create_object(ObjectType object, float x, float y, float z);  //add another object to scene
  	void reset();		//reset the scene

};

#endif
