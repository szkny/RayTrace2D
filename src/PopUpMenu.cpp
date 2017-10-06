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
void Menu(int val);
void Macro();

void PopUpMenu(void){
	glutCreateMenu(Menu);
	glutAddMenuEntry("Run Macro",2);
	glutAddMenuEntry("Show Mirror Image",1);
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
			Macro();
			break;
		default:
			break;
	}
}

