#ifndef MyGLUT_h_
#define MyGLUT_h_

/***************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#ifdef __APPLE__
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include"Define.h"

/**************** Drawing Function ******************/

/* Drawing String Function (string,position x,position y) */
inline void glDrawString(const char *str, double x0, double y0){
	int size = strlen(str);
	glRasterPos2d(x0, y0);
	for(int i = 0; i < size; ++i){
		char ic = str[i];
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ic);
	}	
}


/* Drawing Small String Function (string,position x,position y) */
inline void glDrawString2(const char *str, double x0, double y0){
	int size = strlen(str);
	glRasterPos2d(x0, y0);
	for(int i = 0; i < size; ++i){
		char ic = str[i];
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, ic);
	}	
}


/* Drawing Big String Function (string,position x,position y) */
inline void glDrawString3(const char *str, double x0, double y0){
	int size = strlen(str);
	glRasterPos2d(x0, y0);
	for(int i = 0; i < size; ++i){
		char ic = str[i];
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ic);
	}	
}



/***************************/

#endif //"MyGLUT_h_"
