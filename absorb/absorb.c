#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NUM 1000
#define TMAX 300

int main()
{
	float data[NUM]={0.0f};
	float w[NUM]={0.0f};
	
	srand(time(NULL));
	
	int i=0,j=0,k=0;
	
	float gamma=0.001f;
	float split=50.0f;
	float shift=20.0f;
	float height=0.1f;
	float res=2.0f;
	float time=10.0f;
	
	float step=20.0f;
	
	char datafile[100];
	char add[100];
	
	float x=0.0f,val=0.0f;
	
	strcpy(datafile,"data");
	
	FILE *ptr;
	FILE *ptr2;
	FILE *ptr3;
	FILE *ptr4;
	
	system("rm cmds");
	
	do { //do this in a loop because it looks cool
		res=100/time;
		for (i=0;i<NUM;i++) { //weight function (Gaussian) --number/shape of peaks
			w[i]=1-height*exp(-gamma*(i-NUM/4-split-shift)*(i-NUM/4-split-shift))-height*exp(-gamma*(i-NUM/4+split-shift)*(i-NUM/4+split-shift))-height*exp(-gamma*(i-3*NUM/4-split-shift)*(i-3*NUM/4-split-shift))-height*exp(-gamma*(i-3*NUM/4+split-shift)*(i-3*NUM/4+split-shift));
		}
		data[0]+=w[0]*(float)(rand()%10*res+90);
		for (i=1;i<NUM;i++) { //some randomness
			
			if (i%3==0) {
				data[i]+=w[i]*(float)(rand()%4*res+91);
			} else if (i%5==0) {
				data[i]+=w[i]*(float)(rand()%5*res+90);
			} else if (i%7==0) {
				data[i]+=w[i]*(float)(rand()%6*res+89);
			} else {
				data[i]+=w[i]*(float)(rand()%3*res+92);
			}
		}
	
		ptr=fopen(datafile,"w");
	
		for (i=0;i<NUM;i++) {
			fprintf(ptr,"%f\t%f\n",(float)i,data[i]);
		}
	
		fclose(ptr);
	
		ptr2=fopen("cmds","a");
		if ((time+step)<TMAX) {
			fprintf(ptr2,"%s\n%s\n","set terminal png","set output \"outfile.png\"");
			fprintf(ptr2,"%s%s%s\n%s\n%s\n","plot \"data",add,"\" using 1:2 with points 7","pause 0.1","clear");
		} else {
			fprintf(ptr2,"%s%s%s\n%s\n","plot \"data",add,"\" using 1:2 with points 7","pause mouse");
			ptr3=fopen(datafile,"r");
		}
	
		fclose(ptr2);
		
		
		time+=step;
		strcat(datafile,"A");
		strcat(add,"A");
		
	} while (time<TMAX);
	
	
	ptr4=fopen("finaldata","w");
	for (i=0;i<NUM;i++) {
		fscanf(ptr3,"%f\t%f\n",&x,&val);
		fprintf(ptr4,"%f\t%f\n",x,val);
	}
	fclose(ptr3);
	fclose(ptr4);
	
	system("gnuplot cmds");
	
	system("rm data*");

	
	
	
	return 0;
}
