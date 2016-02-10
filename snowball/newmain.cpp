/********************************************************************
James Burton
Derek Cook
Jason Gossett

December 7, 2001
CPSC 411-01


Snowball Throwing Simulation   Final Project


To Run on SGI: 
    make -f Makefile.sgi

Controls:  
    Look around with the mouse.
    Shoot with the middle mouse button.
    Arrow keys are used for strafe.

We ran out of time, but we intended to make the following enhancements:
    -Enable textures such as a pine needle texture for the trees 
    -Create multiple different environments with different styles for 
        the levels
    -Enable shadowing for more realistic look
    -Enable night courses

What is available: 
    -Physics for bullet include gravity and trajectory
    -Methods created for ease of additional course creation
    -Lighting is enabled
    -Ability to progress through levels by hitting all targets
    -Hours of entertainment



************************************************************************/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glx.h>
#include <string>
#include <iostream>

#include "random.h"
#include "Light.h"
#include "target.h"
#include "tree.h"
#include "bullet.h"
#include "Timer.h"
#include "ground.h"
#include "objectmanager.h"
#include "scene.h"



using namespace std;

#include "trigtables.h" //**** all those nice trig functions *****

#define CDEPTH 5        //**** size of red green and blue ****

#define RADIUS 128      //**** radius of circle in roll window ****

const double PI =  atan(1)*4;

int vattrib[] = {

GLX_RGBA, GLX_DOUBLEBUFFER,
GLX_RED_SIZE, CDEPTH,
GLX_GREEN_SIZE, CDEPTH,
GLX_BLUE_SIZE, CDEPTH,
GLX_DEPTH_SIZE, 1,
None
};


//*** function prototypes *****

//**** from the flight sim ****
inline void redo(int);
void init(void);
void display_me(void);
void reset(int);



/*** Global Variables *****/
extern CRandom rando;

const int width = 720;
const int height = 720;
const int NUM_LIGHTS = 2;

int list_number = 0;
Display * display;
Window rootw, win, mousewin, rollwin;
struct point eyept, viewpt, up; 
int azimuth=0;
int elevation=width/2;
int roll=width/2;
GC wgc, rgc;
int current_level;


Light  **  light;
ObjectManager theObjects;
SceneManager theScenery;

Timer timer;

int main(int argc, char * argv[]){

        XSizeHints whisper;
        XEvent report;
        unsigned long eventmask;
        int screen;
        XVisualInfo *pgob;
        XSetWindowAttributes attrib;
        GLXContext ctx;
        XColor white, black, red;
        int bsz;
        int atemp;
        int option;
        char temp[64];

        current_level = 0; 

        //***** for detecting key values *******

        KeySym key;
        XComposeStatus cstat;
        int size = 32;
        char keyname[32];
        keyname[0]=0;

        //****** check argc *******
	    glutInit(&argc, argv);

        //**** Make sure you can open the display ****

        if((display = XOpenDisplay(NULL))==NULL){
                fprintf(stderr,"Can't open display\n");
                exit(1);
        }

        screen = DefaultScreen(display);

        rootw = RootWindow(display,screen);


        //****** Set Visual Settings and Colors ******

        pgob = glXChooseVisual(display,screen,vattrib);

        attrib.colormap = XCreateColormap(display,rootw,pgob->visual,AllocNone);


        white.red = 0xffff;
        white.green = 0xffff;
        white.blue = 0xffff;
        black.red =  0;
        black.green = 0;        
        black.blue = 0;
        red.red = 0xffff;
        red.blue = 0;
        red.green = 0;

        XAllocColor(display,attrib.colormap,&white);
        XAllocColor(display,attrib.colormap,&black);
        XAllocColor(display,attrib.colormap,&red);
        
        attrib.background_pixel = white.pixel;
        attrib.border_pixel = black.pixel;

        bsz = 0;        //***border size***
        
        //*********** Create the Window **********

        win = XCreateWindow(display,rootw,0,0,width,height,bsz,pgob->depth,InputOutput,pgob->visual,CWBorderPixel|CWColormap|CWBackPixel,&attrib);

        //********** Set Graphics Context ********
        
        wgc = XCreateGC(display,win,0,NULL);
        ctx = glXCreateContext(display,pgob,NULL,True);
        glXMakeCurrent(display,win,ctx);

        //* Whisper flags *

        whisper.flags = PSize | PPosition;
        whisper.width = width;
        whisper.height = height;

        XSetStandardProperties(display,win,"John Elway's South Park Snowball Challenge","snowball",None,argv,argc,&whisper);

        
        whisper.flags = PSize | PPosition;
        whisper.width = 256;
        whisper.height = 256;


        eventmask = ExposureMask|PointerMotionMask|ButtonPressMask|ButtonReleaseMask|KeyPressMask;
        
        XSelectInput(display,win,eventmask);

        XMapWindow(display,win);
        
	        
        XNextEvent(display,&report);
        
        while(report.type!=Expose){
           XNextEvent(display,&report);
        }


	light = new Light*[NUM_LIGHTS];
	light[0] = new Light(0,1.0,1.0,1.0,4.0,9.0,25.0,-8.0,-1.0,-50.0);     //main light
	light[1] = new Light(1,0.7,0.7,0.7,-4.0,9.0,-25.0,8.0,-1.0,50.0);     //back light


        timer.start();		//start the timer
        init();			//set up display properties
        display_me();		//set up level 1

        while(1){

                switch(report.type){
                        
                        case Expose:    
                                
                                        option = 0;
                                        
                                        break;
                                                                        
                                        
                        case KeyPress:  
                                        XLookupString(&report.xkey,keyname,size,&key,&cstat);
                                        switch (key){

                                                case XK_Up:

                                                        //***** Zoom in *****
                                                        option = 1;
                                                        break;

                                                case XK_Down:

                                                        //***** Zoom out ****
                                                        option = 2;
                                                        break;

                                                case XK_Left:
                                                
                                                        //**** strafe left ****
                                                
                                                        option = 5;
                                                        break;
                                                
                                                
                                                case XK_Right:
                                                      
                                                      //====== strafe right =======//
                                                      
                                                       option = 4;
                                                       break;

						
                                                case XK_Escape:
                                                        
                                                        /***** Exit *****/
                                                        glXDestroyContext(display,ctx);
                                                        XCloseDisplay(display);
                                                        exit(0);
                                                
                                                case XK_space:
                                                        option = 6;
                                                        break;
                                                
                                                default: break; 
                                        }
                                        break;                                  
                        case ButtonPress:
                                        switch(report.xbutton.button){

						//====== zoom in =====//
                                                case 1: option = 1; break;
                                                
                                                //===== fire =====//	
                                                case 2: option = 6; break;
                                                        
                                                     
                				//===== zoom out ======//
                                                case 3: option = 2; break;
                                        }
                                     
                                        break;
                        case ButtonRelease:

                                        //**** button release - do nothing ****

                                        option = 0;
                                        break;
                                        

                        case MotionNotify:
                                        while(XCheckMaskEvent(display,PointerMotionMask,&report)!=NULL);
                                        
                                        
                                        azimuth = (report.xbutton.x+width/2)%width;
                                        
                                        if(azimuth>((width+1)/2)-1) atemp = azimuth-width;
                                           else atemp = azimuth;
                                        
                                        elevation = ((width-report.xbutton.y)/2+(width/4));
                                        option = 3;
                                        break;  
                                        
                        default: sleep(1);
                }
                
                do{
                redo(option);                  //***** redo drawing *****
                theObjects.draw_text();		//***** draw on screen message
                glXSwapBuffers(display,win);    //***** swap buffers ****
                glFinish();
		if(report.type == KeyPress || option == 6) option = 0;
		
                
                }while(XCheckMaskEvent(display,eventmask,&report)==NULL);
                
                                        
                
        }

        return 0;
}//*** end main ***

//****************************************************************************
inline void redo(int i){

        struct point viewdir, perpend;
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	int q;

                
        switch (i){

                case 1: 
                     
	                //**** Zoom in ******
                        viewdir.x = viewpt.x - eyept.x;
                        viewdir.y = viewpt.y - eyept.y;
                        viewdir.z = viewpt.z - eyept.z;

                        eyept.x += 0.1 * viewdir.x;	//eyept.y is constant (stay on the ground)
                        eyept.z += 0.1 * viewdir.z;

                        viewpt.x += 0.1 * viewdir.x;
                        viewpt.z += 0.1 * viewdir.z;
                        
               
                        break;
                case 2:
                        //****** Zoom out *****
                        viewdir.x = viewpt.x - eyept.x;
                        viewdir.y = viewpt.y - eyept.y;
                        viewdir.z = viewpt.z - eyept.z;

                        eyept.x -= 0.1 * viewdir.x;
                        eyept.z -= 0.1 * viewdir.z;

                        viewpt.x -= 0.1 * viewdir.x;
                        viewpt.z -= 0.1 * viewdir.z;
                      

                        
                        break;
                case 3:
                        
                        //***** azimuth, elevation, & roll *****

                        viewdir.x = -sin_table[azimuth]*cos_table[elevation];
                        viewdir.y = sin_table[elevation];
                        viewdir.z = cos_table[azimuth]*cos_table[elevation];

                        viewpt.x = eyept.x + viewdir.x;
                        viewpt.y = eyept.y + viewdir.y;
                        viewpt.z = eyept.z + viewdir.z;
                        
                        up.x = sin_table[roll]* cos_table[azimuth]+sin_table[azimuth]*cos_table[roll]*sin_table[elevation];
                        up.y = cos_table[roll]*cos_table[elevation];
                        up.z = sin_table[azimuth]*sin_table[roll] - cos_table[azimuth]*sin_table[elevation]*cos_table[roll];
                        

                break;
                
                case 4:
                        //==== strafe =====//
                        
                        viewdir.x = viewpt.x - eyept.x;
                        viewdir.y = viewpt.y - eyept.y;
                        viewdir.z = viewpt.z - eyept.z;
                        
                        perpend.x = viewdir.y*up.z - viewdir.z*up.y;
                        perpend.y = viewdir.z*up.x - viewdir.x*up.z;
                        perpend.z = viewdir.x*up.y - viewdir.y*up.x;
                  
                        eyept.x += 0.1 * perpend.x;
                        eyept.z += 0.1 * perpend.z;

                        viewpt.x += 0.1 * perpend.x;
                        viewpt.z += 0.1 * perpend.z;


                        break;  
                        
               case 5:
                        //***** strafe the other way *****
                        viewdir.x = viewpt.x - eyept.x;
                        viewdir.y = viewpt.y - eyept.y;
                        viewdir.z = viewpt.z - eyept.z;
                        
                        //****** find perpendicular direction *****
                        perpend.x = viewdir.y*up.z - viewdir.z*up.y;
                        perpend.y = viewdir.z*up.x - viewdir.x*up.z;
                        perpend.z = viewdir.x*up.y - viewdir.y*up.x;
                        
                        eyept.x -= 0.1 * perpend.x;
                        eyept.z -= 0.1 * perpend.z;

                        viewpt.x -= 0.1 * perpend.x;
                        viewpt.z -= 0.1 * perpend.z;

			break;

		case 6:
                        viewdir.x = viewpt.x - eyept.x;
                        viewdir.y = viewpt.y - eyept.y;
                        viewdir.z = viewpt.z - eyept.z;
			theObjects.fire(eyept,viewdir);
			break;

                        
               default: break;
        }
        
        	
                        glPushMatrix();
                        glMatrixMode(GL_MODELVIEW);             /* Redo LookAt Function */
                        glLoadIdentity();
                        gluLookAt(eyept.x,eyept.y,eyept.z,viewpt.x,viewpt.y,viewpt.z,up.x,up.y,up.z);
            				

			  
			  theScenery.display_scene();
			  
			  theObjects.animate();
			  
			  theObjects.collision_detection();
			  


                     for(q = 0; q < NUM_LIGHTS; q++)
			light[q]->update(); 	
		
	             glPopMatrix();
	             
	             if(theObjects.is_cleared()){ sleep(3); reset(++current_level); }
  

}




/**************************************************************/
void display_me(){
 
 	theScenery.create_object(GROUND_OBJECT,0.0,-0.3,0.0);
	theScenery.create_object(TREE_OBJECT,4.0, -0.3, -8.0);
        theScenery.create_object(TREE_OBJECT,4.0, -0.3, -3.0);
        theScenery.create_object(TREE_OBJECT,-5.0, -0.3, -1.0);
	theScenery.create_object(TREE_OBJECT,2.0, -0.3, 4.0);
        theScenery.create_object(TREE_OBJECT,-5.0, -0.3, -5.0);
        theScenery.create_object(TREE_OBJECT,-8.0, -0.3, -10.0);
	

	theObjects.create_target(-3.7, 0.6, -7.0);
	theObjects.create_target(0.0, -0.3, 0.0);
	theObjects.create_target(4.0, -0.2, -5.5);
	theObjects.create_target(5.0, -0.1, 0.0);
	theObjects.create_target(0.0, 0.0, -18.0);


	
}

/***********************************************************************/

void init(){       

        eyept.x = 0.0; eyept.y = 0.0; eyept.z = 4.0;
        viewpt.x = 0.0; viewpt.y  = 0.0; viewpt.z = 0.0;
        up.x = 0.0; up.y = 1.0; up.z = 0.0;


        glDrawBuffer(GL_BACK);
        glutInitDisplayMode(GLUT_DEPTH);
        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);

        glClearColor(0.7,0.7,0.7,1.0);  //light gray
        glClear(GL_COLOR_BUFFER_BIT);
        glPolygonMode(GL_FRONT,GL_FILL);


        for(int q = 0; q < NUM_LIGHTS; q++)
	light[q]->initialize(); 														

	//initialize the fog

	GLfloat fogColor[4] = {1.0,1.0,1.0,1.0};	//snow!
	
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE,GL_EXP);
	glFogfv(GL_FOG_COLOR,fogColor);
	glFogf(GL_FOG_DENSITY,0.05);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START,1.0);
	glFogf(GL_FOG_END,5.0);
	
   
           
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, static_cast<double>(width)/height, 0.1, 50.0);
   

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

				glPushMatrix();
        gluLookAt(eyept.x,eyept.y,eyept.z,viewpt.x,viewpt.y,viewpt.z,up.x,up.y,up.z);
				glPopMatrix();

	
   
}


//=============================================================

void reset(int level){


        eyept.x = 0.0; eyept.y = 0.0; eyept.z = 4.0;
        viewpt.x = 0.0; viewpt.y  = 0.0; viewpt.z = 0.0;
        up.x = 0.0; up.y = 1.0; up.z = 0.0;


	theScenery.reset();
	theObjects.reset();

	int i;
	int number_scenery = rando.number(4,10);
	
	for(i = 0; i < number_scenery; i++)
		theScenery.create_object(static_cast<ObjectType>(rando.number(0,2)),rando.number(-100,100)/10.0,-0.5,rando.number(-100,100)/10.0);

	for(i = 0; i < 5+(2*level); i++)
		theObjects.create_target(rando.number(-100,100)/10.0, rando.number(0,100)/33.333, rando.number(-100,100)/10.0);



}


/***************************************************************/
