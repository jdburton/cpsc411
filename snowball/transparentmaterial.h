#include "material.h"

#ifndef TMATERIAL_H
#define TMATERIAL_H

class TransparentMaterial : public Material {

//Material with an alpha value

public:

	TransparentMaterial(float dr, float dg, float db, float da, float sr = 0.2, float sg = 0.2, float sb = 0.2, float sa = -1.0,float shine = 2.0);
	


};

#endif
