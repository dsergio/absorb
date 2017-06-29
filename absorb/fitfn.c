//function file
//
//
//
void extract()
{
	int i,j=0,k,l=0;

	/*******************
	struct datarr data[2]; // array of structs (arrays)
	data[0]=readfromfile("finaldata");
	data[1]=readfromfile("len2");
	
	for (i=0;i<NUM-10;i++) {
		data[2].dat[i]=0;
		if (data[1].dat[i]>2) {
			//for index i, if len>N, set newdata["j"] to data[i]
			for (k=j;k<data[1].dat[i]+j;k++) {
				data[2].dat[k]=data[0].dat[i+l]; 
				printf("%d\t%f\n",i,data[1].dat[i]);
				l++;
			}
			l=0;
			j=k;
		}
	}

	
	sendtofile(data[2].dat,"peaks",1,j);
	dispdata("peaks");
	**********************/
	
	
	struct datarr data;
	data=readfromfile("finaldata");
	
	
	
	
}
void fit(float data[NUM]) // fit function
{
	int i,j=0,k;
	int len[NUM]={0};
	float average=averageofdata(data);
	
	FILE *ptr4;
	FILE *ptr5;
	
	for (i=0;i<NUM;i++) {
		if (fabs(data[i]-average)>(average*0.07)) {
			printf("%f\t%f\n",conv(i),data[i]);
			j++;
		} else {
			len[i]=j;
			j=0;
		}
	}
	
	ptr4=fopen("len","w");
	for (i=0;i<NUM;i++) {
		if (len[i]>2) {
			fprintf(ptr4,"%d\t%d\n",i,len[i]);
		}
	}
	fclose(ptr4);
	
	ptr5=fopen("len2","w");
	for (i=0;i<NUM;i++) {
		fprintf(ptr5,"%d\t%d\n",i,len[i]);
	}
	fclose(ptr5);
	
}
void fit2(float data[NUM]) // another fit function
{
	int i,j,k;
	float m=0.0f, b=0.0f;
	float fm=0.0f,fb=0.0f;
	
	float diff=0.0f;
	float mdiff=10000.0f;
	float fit[NUM]={0.0f};
	
	for (i=0;i<=NUM-10;i+=9) {
		for (m=-100.0f;m<100.0f;m+=1.0f) {
			for (b=-10000.0f;b<10000.0f;b+=10.0f) {
				
				diff=0.0f;
				for (j=i;j<i+10;j++) {
					fit[j]=b+m*(float)j;
					
					diff+=(float)pow(data[j]-fit[j],2);
				}
				if (diff<mdiff) {
					mdiff=diff;
					fm=m;
					fb=b;
				}
			}
			
		}
		mdiff=10000.0f;
		for (j=i;j<i+10;j++) {
			//printf("%f\n",fb);
			fit[j]=fb+fm*(float)j;
		}
		
	}
	sendtofile(fit,"fitdata",1,NUM);
	dispdata2("finaldata","fitdata");
	dispdata("fitdata");
	
}
void sendtofile(float data[NUM], char *name, int option, int size) //write data to file
{
	FILE *ptr2;
	int i;
	ptr2=fopen(name,"w");
	if (option==0) {
		for (i=0;i<size;i++) {
			fprintf(ptr2,"%f\t%f\n",conv(i),data[i]);
		}
	} else {
		for (i=0;i<size;i++) {
			fprintf(ptr2,"%d\t%f\n",i,data[i]);
		}
	}
	fclose(ptr2);
}
struct datarr readfromfile(char *name) //read data from file (file)
{
	struct datarr data;
	int i,j;
	FILE *ptr;
	ptr=fopen(name,"r");
	
	for (i=0;i<NUM;i++) {
		//fscanf(ptr,"%f\t%f\n",&j,&data.dat[i]);
		fscanf(ptr,"%f\n",&data.dat[i]);
	}
	fclose(ptr);
	return data;

}
void printdata(float data[NUM]) //simply print data
{
	int i;
	for (i=0;i<NUM;i++) {
		printf("%f\n",data[i]);
	}
}
void dispdata(char *name) // use gnuplot to display data
{
	FILE *ptr3;
	ptr3=fopen("cmds2","w");
	fprintf(ptr3,"%s%s%s\n%s\n","plot \"",name,"\" using 1:2 with lines","pause mouse");
	fclose(ptr3);
	system("gnuplot cmds2");
	
}
void dispdata2(char *name, char *name2) // use gnuplot to display data
{
	FILE *ptr;
	ptr=fopen("cmds","w");
	fprintf(ptr,"%s%s%s%s%s\n%s\n","plot \"",name,"\" with points 1, \\\n\t\"",name2,"\" with lines","pause mouse");
	fclose(ptr);
	system("gnuplot cmds");
	
}
float averageofdata(float data[NUM]) //find average value
{
	int i;
	float val=0.0f;
	for (i=0;i<NUM;i++) {
		val+=data[i];
	}
	return val/NUM;
}
float background(float data[NUM]) //find background
{
	int i,j,k;
	float val=0.0f,b=0.0f;
	float avg[NUM/10+1]={0.0f};
	
	k=0;
	for (i=0;i<NUM-10;i+=10) {
		for (j=0;j<10;j++) {
			val+=data[i+j];
		}
		avg[k]=val/10;
		if (avg[k]>b)
			b=avg[k];
		k++;
		val=0.0f;
		//printf("%f\n",avg[i]);
	}
	printf("average: %f background: %f",averageofdata(data),b);
	
	//sendtofile(avg,"name",1,NUM/10+1);
	//dispdata("name");
	
	return b;
}

void smooth(float data[NUM], char *name) // smooth function
{
	int i,j,k;
	float average=0.0f,val=0.0f;
	
	for (i=0;i<NUM-10;i++) {
		for (k=0;k<11;k++) {
			average+=data[i+k];
		}
		val=average/(k+1);
		average=val;
		data[i]=average;
	}
	for (i=NUM;i>NUM-10;i--) {
		for (k=0;k<11;k++) {
			average+=data[i-k];
		}
		val=average/(k+1);
		average=val;
		data[i]=average;
	}
	sendtofile(data,name,0,NUM); //send (modified) data to file
}
float conv(int l)
{
	return (float)l*0.001-0.5; //velocity of sorts--since there's 1000ish "channels"
}
