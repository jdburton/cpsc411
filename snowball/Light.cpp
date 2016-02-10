#include "Light.h"



Light::Light(){

        int i;

        GLfloat amb[] = {1.0,1.0,1.0,0.0};       //turn all ambient off
        GLfloat dif[] = {1.0,1.0,1.0,0.0};       //default:  white light
        GLfloat spec[] = {1.0,1.0,1.0,0.0};      //specular is white
        GLfloat pos[] = {0.0,5.0,0.0,1.0};
        GLfloat dir[] = {0.0,-1.0,0.0,1.0};
        
        ambient = new GLfloat[4];
        diffuse = new GLfloat[4];
        specular = new GLfloat[4];
        position = new GLfloat[4];
        direction = new GLfloat[4];
        
        for(i = 0; i < 4; i++){
           ambient[i] = amb[i];
           diffuse[i] = dif[i];
           specular[i] = spec[i];
           position[i] = pos[i];
           direction[i] = dir[i];
        
        
        }

        index = 0;
        
 
}

Light::Light(int idx, const GLfloat * c,const GLfloat * p,const GLfloat * d){

        index = idx;

        int i;
        
        GLfloat amb[] = {0.0,0.0,0.0};   //turn all ambient off
        GLfloat spec[] = {1.0,1.0,1.0};  //specular is white
        
        ambient = new GLfloat[4];
        specular = new GLfloat[4];
        diffuse = new GLfloat[4];
        direction = new GLfloat[4];
        position = new GLfloat[4];
        
        for(i = 0; i < 3; i ++){
        
           ambient[i] = amb[i];
           specular[i] = spec[i];
           direction[i] = d[i];
           position[i] = p[i];
           diffuse[i] = c[i];
                
        }
        
        ambient[4] = 0.0;
        specular[4] = 0.0;
        
        diffuse[4] = 0.0;
        position[4] = 1.0;
        direction[4] = 1.0;
}

Light::~Light(){

        delete[] ambient;
        delete[] diffuse;
        delete[] specular;
        delete[] position;
        delete[] direction;


}

void Light::initialize(){

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,1);

		glLightfv(GL_LIGHT0+index,GL_AMBIENT,ambient);
		glLightfv(GL_LIGHT0+index,GL_DIFFUSE,diffuse);
		glLightfv(GL_LIGHT0+index,GL_SPECULAR,specular);
	
		glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0+index);

}

Light::Light(int idx, GLfloat cr, GLfloat cg, GLfloat cb, GLfloat px, GLfloat py, GLfloat pz, GLfloat dx, GLfloat dy, GLfloat dz){
				
				int i;

        GLfloat amb[] = {0.2,0.2,0.2,0.0};       //turn all ambient off

        ambient = new GLfloat[4];
        diffuse = new GLfloat[4];
        specular = new GLfloat[4];
        position = new GLfloat[4];
        direction = new GLfloat[4];

        for(i = 0; i < 4; i++){
           ambient[i] = amb[i];
          }

				diffuse[0] = specular[0] = cr;
				diffuse[1] = specular[1] = cg;
				diffuse[2] = specular[2] = cb;
				diffuse[3] = specular[3] = 0.0;

				position[0] = px;
				position[1] = py;
				position[2] = pz;
				position[3] = 1.0;
			
				direction[0] = dx;
				direction[1] = dy;
				direction[2] = dz;
				direction[3] = 1.0;

				index = idx;
				
}


void Light::update(){

		glLightfv(GL_LIGHT0+index,GL_POSITION,position);
	  glLightfv(GL_LIGHT0+index,GL_SPOT_DIRECTION,direction);


}

