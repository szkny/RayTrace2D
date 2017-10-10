/*
*	PopupMenu Configurations
*/

#ifdef __APPLE__
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<MyGLUT.h>

extern bool SFLAG;
extern bool SECONDflag; //defined in Objects.cpp
void Menu(int val);

// fucntion declaration (defined in Objects.cpp)
void Macro();
void CreateVirtualImage();

void PopUpMenu(void){
	glutCreateMenu(Menu);
	glutAddMenuEntry("Show Mirror Image",1);
	glutAddMenuEntry("Number of Reflection",2);
	glutAddMenuEntry("Run Macro",3);
	glutAddMenuEntry("Quit",0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Menu(int val){
	switch(val){
		case 0: /* Quit */
			exit(0);
		case 1:
			if(SFLAG) SFLAG = false;
			else      SFLAG = true;
			break;
		case 2:
			if(SECONDflag) SECONDflag = false;
			else SECONDflag = true;
			CreateVirtualImage();
			break;
		case 3:
			Macro();
			break;
		default:
			break;
	}
}

