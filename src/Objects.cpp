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

#include<MyGLUT.h>
#include<Hue2rgb.h>
#include<Define.h>

#include<Utility.h>
#include<Boundary.h>
#include<Image.h>
#include<vector>

bool SFLAG = true;
extern bool MFLAG;
extern bool VFLAG;

/* clock time */
clock_t FrameTbase = 0;   // for frame rate
int FrameCounter   = 0;   // for frame rate
int TmpCounter     = 0;   // for frame rate
double FrameTimer  = 0.0; // for frame rate

/* size of scintillator */
double x_max = 15./2.0;
double y_max = 15./2.0;

/* size of light guide */
double guide_length = 4.0;
double x_lgd = x_max + guide_length;
double y_lgd = 4.6/2.0;

/* size of pmt tube */
double tube_length = 1.0;
double x_pmt = x_lgd + tube_length;
double y_pmt = y_lgd;

/* center of angle */
vector2d center = {0.0,0.0};

vector2d pmti;
vector2d pmtf;

double Range  = 100.;

extern double windowW,windowH;

std::vector<boundary> bounds;
image images( x_pmt,-y_pmt, x_pmt, y_pmt);

unsigned int sizeinit = 0;

void CreateVirtualImage(void){
	while(bounds.size()>sizeinit){
		bounds.pop_back();
	}
	images.clear();

	// first time reflection
	for(unsigned int i=0;i<sizeinit;++i){
		images.mirror(bounds[i],0);
		for(unsigned int j=0;j<sizeinit;++j){
			images.mirror(bounds[i],bounds[j]);
		}
	}

	// second time reflection
	unsigned int Ni = images.ID.size();
	unsigned int BoundSize = bounds.size();
	for(unsigned int i=1;i<Ni;++i){
		unsigned int Nj = images.ID[i].size();
		if(Nj==0) continue;
		// printf("[%d][%d] %d\n",i,Nj,images.ID[i][Nj-1]);
		for(unsigned int j=0;j<BoundSize;++j){
			int BoundIDsize = bounds[j].ID.size();
			if(1<BoundIDsize){
				int imageID = images.ID[i][Nj-1];
				int boundID = bounds[j].ID[BoundIDsize-2];
				if(imageID==boundID){
					// printf("[%d][%d] %d\t[%2d] %d\n",i,Nj-1,imageID,j,boundID);
					images.mirror(bounds[j],i);
					for(unsigned int k=0;k<BoundSize;++k){
						printf("[%2d]\t[%2d]\n",j,k);
						// images.mirror(bounds[i],bounds[j]);
					}
				}
			}
		}
	}

	images.setsolidangle(center);
	fflush(stdout);
}

void ObjectsInit(void){
	bounds.reserve(500);
	bounds.push_back(boundary(0,-x_max, y_max, x_max, y_max)); //body
	bounds.push_back(boundary(1,-x_max,-y_max, x_max,-y_max)); //body
	bounds.push_back(boundary(2,-x_max,-y_max,-x_max, y_max)); //body
	bounds.push_back(boundary(3, x_max, y_max, x_lgd, y_lgd)); //guide
	bounds.push_back(boundary(4, x_max,-y_max, x_lgd,-y_lgd)); //guide
	bounds.push_back(boundary(5, x_lgd, y_lgd, x_pmt, y_pmt)); //tube
	bounds.push_back(boundary(6, x_lgd,-y_lgd, x_pmt,-y_pmt)); //tube
	sizeinit = bounds.size();
	CreateVirtualImage();
}

void DrawObjects(void){
	if(VFLAG){
		CreateVirtualImage();
	}
	if(MFLAG){
		images.setsolidangle(center);
	}
	images.resize(Range,Range);
	images.draw();
	for(unsigned int i=0;i<sizeinit;++i){
		bounds[i].resize(Range,Range);
		bounds[i].draw();
	}
	if(SFLAG){
		images.drawvirtual();
		for(unsigned int i=sizeinit;i<bounds.size();++i){
			bounds[i].resize(Range,Range);
			bounds[i].color(0.8,0.8,0.8);
			bounds[i].draw();
		}
		images.drawsolidangle();
	}
	// printf("\rboundary: %2lu\timage: %2lu",bounds.size(),images.li.size()-1);
	// fflush(stdout);
}


#define STRING(arg1,arg2,x,y)\
sprintf(s,arg1,arg2);\
glDrawString(s,x/windowW,(windowH-y)/windowH);
/* Draw String Information */
void glDisplayStrings(void){
	FrameTimer = (double)(clock()-FrameTbase)/CLOCKS_PER_SEC;
	if(FrameTimer>=1.0){
		TmpCounter = FrameCounter;
		FrameCounter = 0;
		FrameTbase = clock();
	}
	++FrameCounter;
	/* Strings */
	glColor3d(0.0,0.0,0.0);
	static char s[128];
	STRING("    Frame    : %d fps",TmpCounter,10,20);
	STRING("    Range    : %5.2e",Range,10,35);
	STRING("Guide Length : %5.2f cm",guide_length,10,50);
	STRING("    Angle    : %5.2f %%",images.angle/(2*M_PI)*100,10,65);
	sprintf(s,"  Position   : (%+4.1f,%+4.1f) cm",center.x,center.y);
	glDrawString(s,10/windowW,(windowH-80)/windowH);
}
#undef STRING

double SlideSpeed = 10.;

void glParameterBar(void){
	double x;
	x = images.li[0].x/windowW*SlideSpeed;
	static double y = 15.0;
	glColor3d(0.0,0.0,0.0);
	glLineWidth(1.0);
	glBegin(GL_LINES);
	glVertex2d(0.0,y/windowH);
	glVertex2d(1.0,y/windowH);
	glEnd();
#define plot(a,b)\
glColor3d(a,a,a);\
glBegin(b);\
glVertex2d(x-10/windowW,(y-5)/windowH);\
glVertex2d(x+10/windowW,(y-5)/windowH);\
glVertex2d(x+10/windowW,(y+5)/windowH);\
glVertex2d(x-10/windowW,(y+5)/windowH);\
glEnd();
	plot(0.8,GL_QUADS);
	plot(0.0,GL_LINE_LOOP);
#undef plot
}


void ChangeGuideLength(){
	images.li[0].x = guide_length+x_max+tube_length;
	images.lf[0].x = guide_length+x_max+tube_length;
	bounds[3].lf.x = guide_length+x_max;
	bounds[4].lf.x = guide_length+x_max;
	bounds[5].li.x = guide_length+x_max;
	bounds[6].li.x = guide_length+x_max;
	bounds[5].lf.x = guide_length+x_max+tube_length;
	bounds[6].lf.x = guide_length+x_max+tube_length;
	pmti.x = bounds[5].lf.x;
	pmti.y = bounds[5].lf.y;
	pmtf.x = bounds[6].lf.x;
	pmtf.y = bounds[6].lf.y;
}


void SetRange(int x, int y){
	if((windowH-20<=y&&y<=windowH-10) || MFLAG){
		VFLAG = true;
		guide_length = (double)x/SlideSpeed-x_max;
		if(guide_length<0) guide_length = 0.0;
		else ChangeGuideLength();
	}
}

void SetCenter(int x, int xmouse, int y, int ymouse){
	if(!VFLAG && SFLAG){
		center.x += -(double)(xmouse-x)/10;
		center.y +=  (double)(ymouse-y)/10;
		if(x_max<center.x)  center.x = x_max;
		if(center.x<-x_max) center.x =-x_max;
		if(y_max<center.y)  center.y = y_max;
		if(center.y<-y_max) center.y =-y_max;
	}
}


void Macro(){
	ProgressBar ProBar;
	char DirData[]  = "./data";
	char DirImage[] = "./data/image";
	double min =  0.000000;
	double max = 10.000000;
	double dl  =  0.100000;
	int garray = (max-min)/dl+1;
	int xarray = 151;
	int yarray = 151;
	double dx  = 2*x_max/(double)xarray;
	double dy  = 2*y_max/(double)yarray;

	bool GNUPLOTflag = true;
	FILE *gnu  = popen("gnuplot -persist","w");
	if(gnu==NULL){
		printf("\033[31mcannot open gnuplot.\033[m");
		return;
	}
	if(GNUPLOTflag){
		fprintf(gnu,"set term postscript color\n");
		fprintf(gnu,"set pm3d interpolate 2,2\n");
		fprintf(gnu,"set pm3d map\n");
		fprintf(gnu,"set palette define (0 'black',1 'navy',2 'dark-violet',3 'red',4 'yellow')\n");
		fprintf(gnu,"set xrange[-12:12]\n");
		fprintf(gnu,"set yrange[-8:8]\n");
		fprintf(gnu,"unset key\nset xlabel 'mm'\nset ylabel 'mm'\n");
		fprintf(gnu,"set cbrange[0:25]\n");
		fprintf(gnu,"set title 'Solid Angle (%%)'\n");
	}

	int counter = 0;
	for(guide_length=min;guide_length<=max;guide_length+=dl){
		ChangeGuideLength();
		char filename[100];
		sprintf(filename,"%s/EffMap2d_%02dmm.txt",DirData,(int)(guide_length*10));
		FILE *fp;
		fp = fopen(filename,"w");
		if(fp==NULL){
			printf("\033[31m[error] cannot open \"%s\".\033[m",filename);
			return;
		}
		for(double x=-x_max+dx/2;x<x_max-dx/2;x+=dx){
			++counter;
			ProBar.show(counter,(int)(garray*xarray));
			for(double y=-y_max+dy/2;y<y_max-dy/2;y+=dy){
				center.x = x;
				center.y = y;
				CreateVirtualImage();
				fprintf(fp,"%f\t%f\t%f\n",x,y,images.angle/(2*M_PI)*100);
			}
			fprintf(fp,"\n");
		}
		fflush(fp);
		fclose(fp);
		if(GNUPLOTflag){
			fprintf(gnu,"set output \"%s/EffMap2d_%02dmm.eps\"\n",DirImage,(int)(guide_length*10));
			fprintf(gnu,"set title \"Solid Angle (%%) : Guide Length %d mm\"\n",(int)(guide_length*10));
			fprintf(gnu,"sp \"%s\" u 1:2:3 w pm3d\n",filename);
			fflush(gnu);
		}
	}
	pclose(gnu);
}


