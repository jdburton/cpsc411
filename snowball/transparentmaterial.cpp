#include "transparentmaterial.h"

TransparentMaterial::TransparentMaterial(float dr, float dg, float db, float da, float sr, float sg, float sb, float sa,float shine){
	
	
	if(sa == -1.0) sa = da;		//hack to compensate for prehistoric c++ compiler on SGI machines

	diffuse = new GLfloat[4];
	specular = new GLfloat[4];

	

	diffuse[0] = dr;
	diffuse[1] = dg;
	diffuse[2] = db;
	diffuse[3] = da;

	specular[0] = sr;
	specular[1] = sg;
	specular[2] = sb;
	specular[3] = sa;

	shininess = shine;
	
}
