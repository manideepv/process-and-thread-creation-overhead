/*This program is used to measure the time taken for context-switching
The number of iterations are taken as 10000
rdtsc() is used to measure the number of cycles
rdtsc() is then converted into nano seconds to get the time taken*/
#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include "rdtsc.h"
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sched.h>
#define forkoverhead 11671.106 //overhead due to fork() is defined
void main()
{
	float a=0,b=0,totaltime=0,avgcost=0,diff=0; //initializing varibles to store start and end cycles
	int i,mypipe[2],status,w,res; /*initializing varibles of pipes*/
	pipe(mypipe);
	pid_t pid;
	char p[1];
	p[0]='x';
	//CPU affinity is set to a single core
	cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(0,&mask);
        res=sched_setaffinity(0,sizeof(mask),&mask);
	for(i=0;i<10000;i++)
	{
	        a=rdtsc();  //start cycle count
		pid=fork(); //fork() is invoked
	//check if the process is child or parent
		if(pid==0) 
		{
			write(mypipe[1],(void *)p,1); //write into pipe
			exit(0);
		}
		else
			read(mypipe[0],(void *)p,1); //read from pipe if parent
			b=rdtsc(); //end cycle count
			w=waitpid(pid,&status,0); //wait until process is complete by invoking waitpid()
/*calculate elapsed time. we divide by 2 as two context_switches are involved
also forkoverhead is subtracted*/
		diff=(b-a)/2; 
		totaltime=totaltime+diff;
	}
	avgcost=(((totaltime)*0.294985250)/10000)-forkoverhead;
	printf("cost of context-switch in nanoseconds %f\n",avgcost);
}
