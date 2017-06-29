//main file
//
//
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fit.h"
#include "fitfn.c"

#define NUM 1000

int main()
{
	int i,j,k;

	struct datarr data;
	data=readfromfile("heat1.mos"); //read from file
	//dispdata("heat1.mos"); 
	
	fit2(data.dat);
	
	/*****************************
	//smooth(data.dat,"finaldata--smooth");
	
	//dispdata("finaldata--smooth");
	
	fit(data.dat);
	fit2(data.dat);
	//extract();
	
	//printdata(data.dat); //print data
	
	sendtofile(data.dat,"finaldataconv",0,NUM);
	//dispdata("finaldataconv");
	dispdata("len3");
	k=background(data.dat);
	*****************************/
	
	
	return 0;
}


