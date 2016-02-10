
#include "material.h"

Material::Material(){

	GLfloat d[] = {0.0,0.0,0.0,1.0};
	GLfloat s[] = {0.0,0.0,0.0,1.0};

	diffuse = new GLfloat[4];
	specular = new GLfloat[4];


	for(int i = 0; i<4; i++){

		diffuse[i] = d[i];
		specular[i] = s[i];
  }

	shininess = 2.0;
		

}

Material::Material(float dr, float dg, float db, float sr, float sg, float sb, float shine){


	diffuse = new GLfloat[4];
	specular = new GLfloat[4];

	

	diffuse[0] = dr;
	diffuse[1] = dg;
	diffuse[2] = db;
	diffuse[3] = 1.0;

	specular[0] = sr;
	specular[1] = sg;
	specular[2] = sb;
	specular[3] = 1.0;

	shininess = shine;
	



}


Material::~Material(){

	delete[] diffuse;
	delete[] specular;


}

void Material::set(){

	glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,&shininess);

}

