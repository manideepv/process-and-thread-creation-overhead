/*This program is used to measure the time-taken for process creation
The number of iterations are taken as 10000
rdtsc() is used to calculate the cycles and then this is changed into nanoseconds by multiplying with 1/processor speed
*/
#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
#include<sys/types.h>
#include<signal.h>
#include "rdtsc.h"
#include<sched.h>

void main()
{
	int i,j;
	int res;
        pid_t pid;
	float diff=0,totaltime=0,a=0,b=0;//initializing values to calculate time
	float avg=0;
	//CPU affinity is set so as to run on single core
	cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(0,&mask);
        res=sched_setaffinity(0,sizeof(mask),&mask);
	//loop for 10000 iterations begins
	for(i=0;i<10000;i++)
	{
	a=rdtsc();  //start the count
	pid=fork();  // fork() is invoked
	b=rdtsc();  //end the count
	if(pid==0)  //if child process
	{
	exit(0);
	}
	diff=b-a;
	totaltime=totaltime+diff; //calculation of elapsed time
	}
	avg=((totaltime)*0.294985)/10000; // finding average time and also converting cycles to nanoseconds
	printf("the cost of process creation in nanoseconds is %f\n",avg);
}
