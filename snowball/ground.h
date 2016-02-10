#include "object.h"
#include "material.h"


#ifndef GROUND_H
#define GROUND_H




class Ground : public Object{

private:

	Material * mat;		//material of ground
	
public: 
	Ground();
	~Ground();
	void draw();
	void refresh();
	
	


};




#endif
