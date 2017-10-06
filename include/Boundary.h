#ifndef Boundary_h_
#define Boundary_h_
/*********************************/
#include<Define.h>
#include<vector>

class boundary{
	public:
		std::vector<int> ID; // ID of reflection surfaces
		double windowW,windowH;
		vector2d li;
		vector2d lf;
		vector2d n;
		double R,G,B;

		boundary(int IDself, double xi, double yi, double xf, double yf);
		boundary(std::vector<int> &IDlist, int IDself, double xi, double yi, double xf, double yf);
		boundary(std::vector<int> &IDlist, int IDself, vector2d ini, vector2d fin);
		~boundary(){};
		void resize(int w, int h);
		void color(double r, double g, double b);
		void draw();
};

/*********************************/
#endif
