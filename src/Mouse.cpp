/*
*	Mouse Configurations 
*/

#include<math.h>

#ifdef __APPLE__
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

extern double windowW,windowH;
extern bool SFLAG;
bool MFLAG = false;
bool VFLAG = false;

void SetRange(int x, int y);
void SetCenter(int x, int xmouse, int y, int ymouse);

/* mouse click */
void MouseClick(int button, int state, int x, int y){
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if(state==GLUT_DOWN){
				SetRange(x,y);
			}
			if(state==GLUT_UP){
				VFLAG = false;
				MFLAG = false;
			}
			break;
		default:
			break;
	}
}


/* mouse motion */
void MouseMotion(int x, int y){
	static int xmouse;
	static int ymouse;
	if(MFLAG){
		SetCenter(x,xmouse,y,ymouse);
		if(VFLAG) SetRange(x,y);
	}
	MFLAG  = true;
	xmouse = x;
	ymouse = y;
}


