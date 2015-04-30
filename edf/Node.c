//Node.c
	
	
	#include<stdio.h>
	#ifndef VST_NV_NODE
	#define VST_NV_NODE
	struct node
	{
	int processNumber, arrivalTime, deadline, executionTime;
	struct node *next;
	
	};
	int prnum = 1, totalTime = 0;
	
	inline void getdata(struct node *newobj, struct node *nextlink)
	{
	newobj->processNumber = prnum;
	printf("\nEnter Arrival Time for Process %d:", prnum);
	scanf("%d", &newobj->arrivalTime);
	
	printf("\nEnter Deadline for Process %d:", prnum);
	scanf("%d", &newobj->deadline);
	
	printf("\nEnter Execution Time for Process %d:", prnum);
	scanf("%d", &newobj->executionTime);
	
	newobj->next=nextlink;
	prnum++;
	totalTime += newobj->executionTime;
	}
	/*
	inline void showdata(struct node *obj)
	{
	printf("%d",obj->val);
	}
	*/
	#endif