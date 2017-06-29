//header file
//
//
//
#ifndef H_FIT
#define H_FIT

#define NUM 1000

struct datarr {
	float dat[NUM+1];
};

void sendtofile(float[], char *,int,int); //send data to a file---data,name,option (0 conv, 1 ch), size
struct datarr readfromfile(char *); //read data from file
void printdata(float[]); //print on screen
void dispdata(char *); //print via gnuplot
void dispdata2(char *,char *); //print via gnuplot
float averageofdata(float[]); //return average
float background(float[]); //return background
void smooth(float[], char *); //smooth data, writes to a "smooth" file
void fit(float[]); //find peaks
void fit2(float[]); //find peaks
float conv(int); //channel number conversion to velocity
void extract(void); //extract peaks from background

#endif
