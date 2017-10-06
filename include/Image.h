#ifndef Image_h_
#define Image_h_
/********************************/
#include<Boundary.h>
#include<vector>

class image{
	public:
		double windowW,windowH;
		std::vector< std::vector<int> > ID; // ID of reflection surfaces (ID[No.][surface,...])
		std::vector<vector2d> li;           // image position initial    (li[No.])
		std::vector<vector2d> lf;           // image position final      (lf[No.])

		vector2d A;               // Position of Center Angle
		std::vector<vector2d> B;  // Position of image initial  (B[No.])
		std::vector<vector2d> C;  // Position of image final    (C[No.])
		std::vector<bool> visible;// judgement of visible image (visible[No.])
		double angle;

		image(double xi, double yi, double xf, double yf);
		~image();
		void resize(int w, int h);
		void draw();
		void drawvirtual();
		void drawsolidangle();
		void clear();
		void mirror(boundary bnd, unsigned int id);
		void mirror(boundary bnd, boundary img);
		void setsolidangle(vector2d center);
		// void save(vector2d ini, vector2d fin);
		void instance(vector2d ini, vector2d fin);
};

/********************************/
#endif
