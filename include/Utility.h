#ifndef UTILITY_H_
#define UTILITY_H_
/*****************************************/
#include<iostream>
#include<string>

class ProgressBar{
	private:
		std::string Bar;
		std::string SingleBar;
		std::string EndBar;
		std::string Cycle;
		unsigned int ci;
		bool flag;
	public:
		inline ProgressBar();
		inline void show(int counter, int loopmax);
};

inline ProgressBar::ProgressBar(){
	Bar       = "";
	SingleBar = "■";
	EndBar    = "                                                  ]";
	Cycle     = ">)|(<-"; 
	// Cycle     = "-\\|/"; 
	ci        = 0;
	flag      = true;
}

inline void ProgressBar::show(int counter, int loopmax){
	double Percentage = counter/((double)loopmax)*100;
	int Percentage_INT = (int)Percentage;
	if(Percentage_INT % 2 == 0){
		if(flag){
			if(1<EndBar.size()){
				Bar += SingleBar;
				EndBar.erase(EndBar.begin());
			}
			flag = false;
		}
	}
	if(Percentage_INT % 2 == 1) flag = true;
	if(Percentage_INT == 100){
		printf( "\r  [\033[32m%s\033[m%s%6.2lf%% done.\n",Bar.c_str(),EndBar.c_str(),Percentage);
	}else{
		printf("\r %c[\033[32m%s\033[m%s%6.2lf%%",Cycle[ci],Bar.c_str(),EndBar.c_str(),Percentage);
	}
	fflush(stdout);
	if(counter%50 == 0){
		++ci;
		if(Cycle.size()<=ci) ci=0;
	}
}

/*****************************************/
#endif

