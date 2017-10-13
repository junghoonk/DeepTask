#include <stdio.h>
#include <stdlib.h>
#include "std_msgs/String.h"

const int Nf = 10;
const float T = 0.02;

float x[Nf]={0.0};
float y[Nf]={0.0};
float z[Nf]={0.0};

void MovementClassifier(bool& mv_flag, float loc[]);
float dist(float x1,float y1, float z1,float x2, float y2,float z2);

void MovementClassifier(bool& mv_flag, float loc[]){
	
	int i ;

	for (i=0; i<Nf-1; i++){
		x[i] = x[i+1];
	}
	for (i=0; i<Nf-1; i++){
		y[i] = y[i+1];
	}
	for (i=0; i<Nf-1; i++){
		z[i] = z[i+1];
	}

	x[Nf-1]=loc[0];
	y[Nf-1]=loc[1];
	z[Nf-1]=loc[2];


	float distance = dist(x[1],y[1],z[1],x[Nf-1],y[Nf-1],z[Nf-1]);	
	if (distance < T){
		mv_flag = false;
	}

}


float dist(float x1,float y1, float z1,float x2, float y2,float z2){
	float distance;
	distance = sqrt( pow((x2-x1),2) + pow((y2-y1),2) + pow((z2-z1),2) );
	return distance;


}
