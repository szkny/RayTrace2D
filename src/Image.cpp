#include<stdio.h>
#include<math.h>

#ifdef __APPLE__
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<Hue2rgb.h>
#include<Image.h>
#include<Boundary.h>
#include<vector>

extern std::vector<boundary> bounds;

image::image(double xi, double yi, double xf, double yf){
	std::vector<int> IDtmp;
	IDtmp.push_back(0);
	ID.push_back(IDtmp);
	vector2d tmpi ={xi,yi};
	vector2d tmpf ={xf,yf};
	li.push_back(tmpi);
	lf.push_back(tmpf);
	B.push_back(tmpi);
	C.push_back(tmpf);
	visible.push_back(true);
	angle = 0.;
}

image::~image(){
}

void image::resize(int w, int h){
	windowW = (double)w;
	windowH = (double)h;
}

void image::draw(){
	glLineWidth(3.);
	glColor3d(1.,0.,0.);
	glBegin(GL_LINES);
	glVertex2d(0.5+li[0].x/windowW,0.5+li[0].y/windowH);
	glVertex2d(0.5+lf[0].x/windowW,0.5+lf[0].y/windowH);
	glEnd();
}

void image::drawvirtual(){
	// glEnable(GL_LINE_STIPPLE);
	// glLineStipple(1, 0xaaaa);
	glLineWidth(2.);
	glColor3d(1.0,0.6,0.6);
	glBegin(GL_LINES);
	for(unsigned i=1;i<this->ID.size();++i){
		glVertex2d(0.5+li[i].x/windowW,0.5+li[i].y/windowH);
		glVertex2d(0.5+lf[i].x/windowW,0.5+lf[i].y/windowH);
	}
	glEnd();
	// glDisable(GL_LINE_STIPPLE);
}

void image::clear(){
	while(this->ID.size()>1){
		ID.pop_back();
		li.pop_back();
		lf.pop_back();
	}
}

void image::mirror(boundary bnd, unsigned int id){
	if(fabs(bnd.li.x-li[id].x)<EPS){
		if(fabs(bnd.li.y-li[id].y)<EPS){
			if(fabs(bnd.lf.x-lf[id].x)<EPS){
				if(fabs(bnd.lf.y-lf[id].y)<EPS){
					return;
				}
			}
		}
	}
	vector2d tmpi;
	vector2d tmpf;
	double denominator = bnd.lf.x-bnd.li.x;
	if(fabs(denominator)>EPS){
		double a = (bnd.lf.y-bnd.li.y)/denominator;
		double b = bnd.lf.y - a*bnd.lf.x;
		tmpi.x = ((1-a*a)*li[id].x+2*a*(li[id].y-b))/(1+a*a);
		tmpi.y = a*(li[id].x+tmpi.x)+2*b-li[id].y;
		tmpf.x = ((1-a*a)*lf[id].x+2*a*(lf[id].y-b))/(1+a*a);
		tmpf.y = a*(lf[id].x+tmpf.x)+2*b-lf[id].y;
	}
	else if(fabs(bnd.lf.y-bnd.li.y)>EPS){
		tmpi.x = 2*bnd.li.x-li[id].x; 
		tmpf.x = 2*bnd.lf.x-lf[id].x; 
		tmpi.y = li[id].y; 
		tmpf.y = lf[id].y; 
	}
	this->ID.push_back(bnd.ID);
	li.push_back(tmpi);
	lf.push_back(tmpf);
	B.push_back(tmpi);
	C.push_back(tmpf);
	visible.push_back(true);
}

void image::mirror(boundary bnd, boundary img){
	if(fabs(bnd.li.x-img.li.x)<EPS){
		if(fabs(bnd.lf.x-img.lf.x)<EPS){
			if(fabs(bnd.li.y-img.li.y)<EPS){
				if(fabs(bnd.lf.y-img.lf.y)<EPS){
					return;
				}
			}
		}
	}
	double denominator = bnd.lf.x-bnd.li.x;
	vector2d tmpi;
	vector2d tmpf;
	if(fabs(denominator)>EPS){
		double a = (bnd.lf.y-bnd.li.y)/denominator;
		double b = bnd.lf.y - a*bnd.lf.x;
		tmpi.x = ((1-a*a)*img.li.x+2*a*(img.li.y-b))/(1+a*a);
		tmpi.y = a*(img.li.x+tmpi.x)+2*b-img.li.y;
		tmpf.x = ((1-a*a)*img.lf.x+2*a*(img.lf.y-b))/(1+a*a);
		tmpf.y = a*(img.lf.x+tmpf.x)+2*b-img.lf.y;
	}
	else{
		tmpi.x = 2*bnd.li.x-img.li.x; 
		tmpf.x = 2*bnd.lf.x-img.lf.x; 
		tmpi.y = img.li.y; 
		tmpf.y = img.lf.y; 
	}
	bounds.push_back(boundary(bnd.ID,bounds.size(),tmpi,tmpf));
}

void image::setsolidangle(vector2d center){
	this->angle = 0.;
	this->A.x = center.x;
	this->A.y = center.y;
	for(unsigned int i=0;i<this->ID.size();++i){
		B[i] = li[i];
		C[i] = lf[i];
		visible[i] = true;
		if(0<i){
			for(unsigned int j=0;j<this->ID[i].size();++j){
				vector2d bi = bounds[ID[i][j]].li;
				vector2d bf = bounds[ID[i][j]].lf;
				B[i].x = li[i].x;
				B[i].y = li[i].y;
				C[i].x = lf[i].x;
				C[i].y = lf[i].y;
				if(!JudgeIntersected(center,this->li[i],bi,bf)\
						||!JudgeIntersected(center,this->lf[i],bi,bf)){
					visible[i] = false;
					break;
				}
			}
		}
		if(visible[i]){
			vector2d AB = {B[i].x-center.x,B[i].y-center.y};
			vector2d AC = {C[i].x-center.x,C[i].y-center.y};
			angle += InteriorAngle(AB,AC);
		}
	}
}

// void image::setsolidangle(vector2d center){
// 	this->angle = 0.;
// 	this->A.x = center.x;
// 	this->A.y = center.y;
// 	for(unsigned int i=0;i<this->ID.size();++i){
// 		B[i] = li[i];
// 		C[i] = lf[i];
// 		visible[i] = true;
// 		if(0<i){
// 			for(unsigned int j=0;j<this->ID[i].size();++j){
// 				vector2d bi = bounds[ID[i][j]].li;
// 				vector2d bf = bounds[ID[i][j]].lf;
// 				B[i].x = li[i].x;
// 				B[i].y = li[i].y;
// 				C[i].x = lf[i].x;
// 				C[i].y = lf[i].y;
// 				// if(!JudgeIntersected(center,this->li[i],bi,bf)||!JudgeIntersected(center,this->lf[i],bi,bf)){
// 				if(!JudgeIntersected(center,this->li[i],bi,bf)){
// 					if(!JudgeIntersected(center,this->lf[i],bi,bf)){
// 						visible[i] = false;
// 						break;
// 					}
// 					// else{
// 					// 	C[i].x = lf[i].x;
// 					// 	C[i].x = lf[i].y;
// 					// 	if(JudgeInTriangle(bi,center,li[i],lf[i])){
// 					// 		vector2d tmp = CrossPoint(center,bi,li[i],lf[i]);
// 					// 		B[i].x = tmp.x;
// 					// 		B[i].y = tmp.y;
// 					// 	}else{
// 					// 		vector2d tmp = CrossPoint(center,bf,li[i],lf[i]);
// 					// 		B[i].x = tmp.x;
// 					// 		B[i].y = tmp.y;
// 					// 	}
// 					// }
// 				}
// 				// else if(!JudgeIntersected(center,this->lf[i],bi,bf)){
// 					// C[i].x = li[i].x;
// 					// C[i].x = li[i].y;
// 					// if(JudgeInTriangle(bi,center,li[i],lf[i])){
// 					// 	vector2d tmp = CrossPoint(center,bi,li[i],lf[i]);
// 					// 	B[i].x = tmp.x;
// 					// 	B[i].y = tmp.y;
// 					// }else{
// 					// 	vector2d tmp = CrossPoint(center,bf,li[i],lf[i]);
// 					// 	B[i].x = tmp.x;
// 					// 	B[i].y = tmp.y;
// 					// }
// 				// }
// 			}
// 		}
// 		if(visible[i]){
// 			vector2d AB = {B[i].x-center.x,B[i].y-center.y};
// 			vector2d AC = {C[i].x-center.x,C[i].y-center.y};
// 			angle += InteriorAngle(AB,AC);
// 		}
// 	}
// 	// printf("\rB: (%5.1f,%5.1f)\tC: (%5.1f,%5.1f)",B[2].x,B[2].y,C[2].x,C[2].y);
// 	// fflush(stdout);
// }
//

void image::drawsolidangle(){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4d(0.0,0.0,1.0,0.5);
	glBegin(GL_TRIANGLES);
	for(unsigned int i=0;i<this->ID.size();++i){
		if(visible[i]){
			glVertex2d(0.5+A.x/windowW,0.5+A.y/windowH);
			glVertex2d(0.5+B[i].x/windowW,0.5+B[i].y/windowH);
			glVertex2d(0.5+C[i].x/windowW,0.5+C[i].y/windowH);
		}
	}
	glEnd();
	glDisable(GL_BLEND);
}

