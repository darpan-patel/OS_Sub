//main
	
	#include<stdio.h>
	#include<stdlib.h>
	#include"llistF.c"
	
	void main()
	{
	int n, i1, i2, time = 0, processToRun;
	int *processRunOrder = NULL;
	struct node *processes = NULL;
	
	printf("Enter total number of processes:");
	scanf("%d",&n);
	
	    for(i1 = 0; i1 < n; i1++)
	{
	processes = insert(processes,NULL);
	}
	processRunOrder = (int*)malloc(totalTime*sizeof(int));
	
	while(processes != NULL)
	{
	processToRun = min_deadline_exec(processes, time);
	if(processToRun < 0)
	{
		processToRun *= -1;
		processes = del(processes, processToRun);
	}
	processRunOrder[time] = processToRun;
	time++;
	}
	
	for(i1 = 1; i1 <= n; i1++)
	{
	printf("\nP[%d]", i1);
	for(i2 = 0; i2 < totalTime; i2++)
	{
		if(processRunOrder[i2] == i1)
			printf("*");
		else
		printf(" ");
	}
	}
	printf("\n");
	free(processRunOrder);
	}
