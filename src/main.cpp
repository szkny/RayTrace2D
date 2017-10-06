/* main.cpp
 *
 *    Ray Tracing 2D
 *     (c) S.Suzuki 2017.10.5
 */
#include<stdio.h>
#include<math.h>

#ifdef __APPLE__
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

/* Function Prototype Declaration */
void WindowCanvas(void);
void Controler(void);
void PopUpMenu(void);
void Display(void);
void Resize(int w, int h);
void MouseClick(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void KeyboardShortcut(unsigned char key, int x, int y);
void Keyboard_sp(int key, int x, int y);

void ObjectsInit();
void DrawObjects();
void glDisplayStrings();
void glParameterBar();


/* main function */
int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	WindowCanvas();
	PopUpMenu();
	Controler();
	
	glutMainLoop();
	return 0;
}

/******** Functions *********/

void WindowCanvas(void){
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("RayTrace2D");
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glClearColor(1.0,1.0,1.0,1.0);
	ObjectsInit();
}


void Controler(void){
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMotion);
	glutKeyboardFunc(KeyboardShortcut);
	glutSpecialFunc(Keyboard_sp);
}


void Display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	DrawObjects();
	glDisplayStrings();
	glParameterBar();
	glutIdleFunc(glutPostRedisplay);
	glutSwapBuffers();
}

double windowW = 0.;
double windowH = 0.;

void Resize(int w, int h){
	glutReshapeWindow(h,h);
	windowW = w;
	windowH = h;
	glViewport(0, 0, w ,h);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
}


