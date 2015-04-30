//llistF.c
	
	#include "node.c"
	#include<stdlib.h>
	
	#ifndef VST_NV_LIST
	#define VST_NV_LIST
	struct node* insert(struct node *list, struct node *predefin)
	{
	struct node *curr = NULL;
	if(predefin == NULL)
	{
		if(list==NULL)
		{
			list=(struct node*)malloc(sizeof(struct node));
			prnum;
			getdata(list,NULL);
		}
		else
		{
			for(curr=list; curr -> next != NULL; curr = curr -> next);
			curr -> next = (struct node*)malloc(sizeof(struct node));
			curr = curr -> next;
			getdata(curr,NULL);
		}
	}
	
	else
	{
		if(list==NULL)
		{
			list=(struct node*)malloc(sizeof(struct node));
			*list = *predefin;
			list -> next = NULL;
		}
		else
		{
			for(curr=list; curr -> next != NULL; curr = curr -> next);
			curr -> next = (struct node*)malloc(sizeof(struct node));
			curr = curr -> next;
			*curr = *predefin;
			curr -> next = NULL;
		}
	}
	return list;
	}
	
	int min_deadline_exec(struct node *start, int time)
	{
	int minValue = 0, prcsnum = 0;
	struct node *list = start;
	if(list == NULL)
		printf("\nList is empty!!!");
	
	else
	{
		for(; list -> arrivalTime > time && list != NULL; list = list -> next);
		minValue = list -> deadline;
		prcsnum = list -> processNumber;
		list = list -> next;
	
		while(list)
		{
			if(list -> deadline < minValue && list -> arrivalTime <= time)
			{
				minValue = list -> deadline;
				prcsnum = list -> processNumber;
			}
			list = list -> next;
		}
	}
	
	for(list = start; list -> processNumber != prcsnum; list = list -> next);
	list -> executionTime -= 1;
	if(list -> executionTime == 0)
	{
		prcsnum *= -1;
	}
	return prcsnum;
	}
	
	int min_slack_exec(struct node *start, int time)
	{
	int minValue = 0, prcsnum = 0;
	struct node *list = start;
	if(list == NULL)
		printf("\nList is empty!!!");
	
	else
	{
		for(; list -> arrivalTime > time && list != NULL; list = list -> next);
		minValue = time - list -> deadline - list -> executionTime;
		prcsnum = list -> processNumber;
		list = list -> next;
	
		while(list)
		{
			if(time - list -> deadline - list -> executionTime < minValue && list -> arrivalTime <= time)
			{
				minValue = time - list -> deadline - list -> executionTime;
				prcsnum = list -> processNumber;
			}
			list = list -> next;
		}
	}
	
	for(list = start; list -> processNumber != prcsnum; list = list -> next);
	list -> executionTime -= 1;
	if(list -> executionTime == 0)
	{
		prcsnum *= -1;
	}
	return prcsnum;
	}
	
	/*void displayLrow(struct node *start)
	{
	if(start == NULL)
		printf("\nList is Empty...");
	
	else
	{
		while(start)
		{
			printf("\t");
			showdata(start);
			start = start->next;
		}
	}
	}*/
	
	struct node* del(struct node *head, int iPrnum) //delets the node whose process number is matched
	{
	int iCnt, iPos;
	struct node *prev = NULL; //maintaining pre
	struct node *delnode = NULL;
	struct node *curr = NULL;
	
	if(head == NULL)
		printf("\n\nThe list is empty");
		
	else
	{
		//////////////////////////////////////////
		curr = head;
		prev = curr;
		iCnt = 1;
		while(curr->next != NULL && iPrnum != curr->processNumber)
		{
			prev = curr;
			curr = curr->next;
			iCnt++;
		}
		////////////////check for the match
		
		if(iCnt == 1 && iPrnum == curr->processNumber) //for deleting the first node
		{
			delnode = curr;
			head = curr->next;
			free(delnode);
		}
		else if(iPrnum == curr->processNumber) //for deleting any other node in between
		{
			delnode = curr;
			prev->next = curr->next;
			free(delnode);
		}
		
		return head;
	}
	}
	#endif
