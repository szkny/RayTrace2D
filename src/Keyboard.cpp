/*
*	Keyboard Shortcuts Configurations 
*/

#ifdef __APPLE__
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<MyGLUT.h>

extern int NMAX;
extern bool SFLAG,LFLAG;

void Macro(); // defined in Objects.cpp

void KeyboardShortcut(unsigned char key, int x, int y){
	switch(key){
		case 'q':
			exit(0);
		case 's':
			if(SFLAG) SFLAG = false;
			else      SFLAG = true;
			break;
		case 'm':
			Macro();
			break;
		default:
			break;
	}
}


void Keyboard_sp(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
			break;
		case GLUT_KEY_DOWN:
			break;
		default:
			break;
	}
}


