#ifndef Define_h_
#define Define_h_

/***************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#ifndef PI
#define PI 3.14159265359
#endif

#ifndef EPS
#define EPS (1.e-8)
#endif

#ifndef Randf_
#define Randf_
//0~1の一様乱数の作成する関数
inline double randf(void){
    //rand();rand();rand();rand();rand();rand();
    return rand()*(1.0/RAND_MAX);
}
#endif

#ifndef Poisson_
#define Poisson_
/* random function (poison distribution) */
inline int poisson(double lambda){
	if( lambda<30 ){
		double x;
		int k = 0;
		x = randf();
		while( x>=exp(-lambda) ) {
			x = x*randf();
			k = k+1;
		}
		return k;
	}
	else{
		double sigma = sqrt(lambda);
		double z = sqrt(-2.0*log(randf()))*sin(2.0*PI*randf());
		int k = lambda+sigma*z;
		return k;
	}
}
#endif

struct vector2d{
	double x;
	double y;
};

struct vector3d{
	double x;
	double y;
	double z;
};

inline vector2d add2d(vector2d a, vector2d b){
	vector2d tmp = {a.x+b.x, a.y+b.y};
	return tmp;
}

inline vector2d sub2d(vector2d a, vector2d b){
	vector2d tmp = {a.x-b.x, a.y-b.y};
	return tmp;
}

inline double inner2d(vector2d a, vector2d b){
	return (a.x)*(b.x)+(a.y)*(b.y);
}

inline vector3d crossproduct(vector3d a, vector3d b){
	vector3d tmp = {
		(a.y)*(b.z)-(a.z)*(b.y),
		(a.z)*(b.x)-(a.x)*(b.z),
		(a.x)*(b.y)-(a.y)*(b.x)
	};
	return tmp;
}

inline double norm2d(vector2d a){
	return sqrt(a.x*a.x+a.y*a.y);
}

inline double norm3d(vector3d a){
	return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
}

inline bool parallel(vector3d a, vector3d b){
	if(norm3d(crossproduct(a,b))<EPS) return true;
	else return false;
}

inline double InteriorAngle(vector2d AB, vector2d AC){
	double ABnorm = norm2d(AB);
	double ACnorm = norm2d(AC);
	if(fabs(ABnorm)>EPS && fabs(ACnorm)>EPS){
		return acos(inner2d(AB,AC)/(norm2d(AB)*norm2d(AC)));
	}
	else
		return 0.0;
}

inline bool JudgeIntersected(vector2d ai, vector2d af, vector2d bi, vector2d bf){
	double tai = (bi.x-bf.x)*(ai.y-bi.y)+(bi.y-bf.y)*(bi.x-ai.x);
	double taf = (bi.x-bf.x)*(af.y-bi.y)+(bi.y-bf.y)*(bi.x-af.x);
	double tbi = (ai.x-af.x)*(bi.y-ai.y)+(ai.y-af.y)*(ai.x-bi.x);
	double tbf = (ai.x-af.x)*(bf.y-ai.y)+(ai.y-af.y)*(ai.x-bf.x);
	return (tai*taf)<=0 && (tbi*tbf)<=0;
}

// inline vector2d CrossPoint(vector2d Ai, vector2d Af, vector2d Bi, vector2d Bf){
// 	vector2d tmp;
// 	double f0 = (Af.y-Ai.y)/(Af.x-Ai.x);
// 	double f1 = (f0*Bf.x-Bf.y)/(-Bi.x+Bi.y+f0*Bf.x-Bf.y);
// 	double f2 = ((1-f1)*Bf.x+f1*Bi.x)/(Af.x-Ai.x);
// 	tmp.x = f2*(Af.x-Ai.x);
// 	tmp.y = f2*(Af.y-Ai.y);
// 	if(fabs(Af.x-Ai.x)<EPS || fabs(-Bi.x+Bi.y+f0*Bf.x-Bf.y)<EPS){
// 		printf(" error: function CrossPoint() needs unparallel vectors.\n");
// 		exit(1);
// 	}
// 	return tmp;
// }


// judgement whether point p is in Triangle ABC or not.
// inline bool JudgeInTriangle(vector2d P, vector2d A, vector2d B, vector2d C){
// 	vector2d AB = sub2d(B,A);
// 	vector2d BC = sub2d(C,B);
// 	vector2d CA = sub2d(A,C);
// 	vector2d AP = sub2d(P,A);
// 	vector2d BP = sub2d(P,B);
// 	vector2d CP = sub2d(P,C);
// 	double c1 = AB.x*BP.y-AB.y*BP.x;
// 	double c2 = BC.x*CP.y-BC.y*CP.x;
// 	double c3 = CA.x*AP.y-CA.y*AP.x;
// 	if((c1>0 && c2>0 && c3>0) || (c1<0 && c2<0 && c3<0)) return true;
// 	else return false;
// }

/***************************/

#endif //"Define_h_"
