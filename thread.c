/*This program measures the time taken for thread creation
the number of iterations are set to 10000
rdtsc() is used to measure the time
The time obtained through rdtsc() is in cycles
This is converted into nanoseconds*/

#define _GNU_SOURCE
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<sys/types.h>
#include "rdtsc.h"
#include<sched.h>

void *start_func(void *), *arg;

void main()
{
        int i,j,res;
        pthread_t tid;
        float diff=0,totaltime=0,a=0,b=0; //initializing values to store the cycle count
        float avg=0;
	//CPU affinity is set to run on a single core
	cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(0,&mask);
        res=sched_setaffinity(0,sizeof(mask),&mask);
	//loop begins
        for(i=0;i<10000;i++)
        {
        a=rdtsc(); //start of cycle count
	pthread_create(&tid, NULL, start_func, arg); //pthread_create() is invoked
	b=rdtsc();  // end of cycle count
	pthread_join(tid,NULL);
        diff=b-a;
        totaltime=totaltime+diff; //overall elapsed time
        }
        avg=((totaltime)*0.294985250)/10000; //average cost and conversion of cycles to nanoseconds
        printf("cost of thread creation in nanoseconds is %f\n",avg);
}

void *start_func(void *arg)
{
	pthread_exit(NULL);
}

