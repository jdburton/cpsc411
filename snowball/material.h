
#include <GL/gl.h>

#ifndef MATERIAL_H
#define MATERIAL_H


class Material {

protected:

		GLfloat * diffuse;	//components of material
		GLfloat * specular;
		GLfloat shininess;

public: 
	Material();
	Material(float dr, float dg, float db,  float sr = 0.2, float sg = 0.2, float sb = 0.2, float shine = 2.0);


	~Material();

	void  set();	//apply the material

};

#endif
