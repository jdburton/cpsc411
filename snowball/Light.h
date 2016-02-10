#include <iostream>
#include <GL/gl.h>

class Light {

   private:
   
        GLfloat * ambient;
        GLfloat * diffuse;
        GLfloat * specular;
        GLfloat * position;
        GLfloat * direction;

	int index;  //which light is it?

   public:
        Light();
        Light(int i, const GLfloat * c,const GLfloat * p,const GLfloat * d);
				Light(int idx, GLfloat cr = 0.0, GLfloat cg = 0.0, GLfloat cb = 0.0, GLfloat px = 0.0, GLfloat py = 10.0, GLfloat pz = 0.0, GLfloat dx = 0.0, GLfloat dy = -1.0, GLfloat dz = 0.0);

				~Light();

				void initialize();
				void update();
				
        
                
   
        


};
