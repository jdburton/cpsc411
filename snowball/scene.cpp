#include "scene.h"
#include "tree.h"
#include "ground.h"

const int SCENE_OBJECTS = 32;

SceneManager::SceneManager(){

		SceneList = new Object*[SCENE_OBJECTS];
		
	 	size = 0;


		int i;
		
		
		
		for(i = 0; i<SCENE_OBJECTS; i++){
     	
				SceneList[i] = new Object;

		}

}

SceneManager::~SceneManager(){

	for(int i = 0; i < SCENE_OBJECTS; i++)
		delete SceneList[i];
		
	delete[] SceneList;


}


void SceneManager::create_object(ObjectType object,float x, float y, float z){

	if(size >= SCENE_OBJECTS) return;
	
	switch(object){
	
	
		case TREE_OBJECT:
		case HILL_OBJECT:	//not implimented yet
		
			SceneList[size] = new Tree(x,-0.3,z);
			break;
		
		case GROUND_OBJECT:
			SceneList[size] = new Ground();
			break;
			
	
		
		default: break;
	}
	
	SceneList[size]->draw();
	
	size++;
}


void SceneManager::reset(){

	size = 0;
	int i;

	for(i = 0; i<SCENE_OBJECTS; i++){
     	
		SceneList[i] = new Object;

	}


}

	
void SceneManager::display_scene(){

	for(int i = 0; i < size; i++){
	
		SceneList[i]->refresh();
	}

}	
	
	

