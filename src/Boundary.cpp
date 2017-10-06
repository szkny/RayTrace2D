#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#ifdef __APPLE__
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<Boundary.h>

boundary::boundary(int IDself, double xi, double yi, double xf, double yf){
	ID.push_back(IDself);
	li.x = xi;
	li.y = yi;
	lf.x = xf;
	lf.y = yf;
	R=0.;G=0.;B=0.;
}

boundary::boundary(std::vector<int> &IDlist, int IDself, double xi, double yi, double xf, double yf){
	for(unsigned i=0;i<IDlist.size();++i)
		ID.push_back(i);
	ID.push_back(IDself);
	li.x = xi;
	li.y = yi;
	lf.x = xf;
	lf.y = yf;
	R=0.;G=0.;B=0.;
}

boundary::boundary(std::vector<int> &IDlist, int IDself, vector2d ini, vector2d fin){
	for(unsigned i=0;i<IDlist.size();++i)
		ID.push_back(i);
	ID.push_back(IDself);
	li.x = ini.x;
	li.y = ini.y;
	lf.x = fin.x;
	lf.y = fin.y;
	R=0.;G=0.;B=0.;
}

void boundary::resize(int w, int h){
	windowW = (double)w;
	windowH = (double)h;
}

void boundary::color(double r, double g, double b){
	R = r;
	G = g;
	B = b;
}

void boundary::draw(){
	// glEnable(GL_LINE_STIPPLE);
	// glLineStipple(1.0, 0x5555);
	glLineWidth(1.);
	glColor3d(R,G,B);
	glBegin(GL_LINES);
	glVertex2d(0.5+li.x/windowW,0.5+li.y/windowH);
	glVertex2d(0.5+lf.x/windowW,0.5+lf.y/windowH);
	glEnd();
	// glDisable(GL_LINE_STIPPLE);
}

