
	//4_LST.c
	
	#include "node.c"
	
	#ifndef VST_NV_QUEUE
	#define VST_NV_QUEUE
	struct Queue
	{
	int prnum;
	struct node *top, *rear;
	};
	
	void insert(struct Queue *que, struct node *predefin)
	{
	struct node *curr = NULL;
	if(predefin == NULL)
	{
		if(que -> rear == NULL)
		{
			que -> rear = (struct node*)malloc(sizeof(struct node));
			getdata(que -> rear, NULL, que -> prnum);
			que -> top = que -> rear;
		}
		else
		{
			que -> rear -> next = (struct node*)malloc(sizeof(struct node));
			que -> rear = que -> rear -> next;
			getdata(que -> rear, NULL, que -> prnum);
		}
	}
	
	else
	{
		if(que -> rear == NULL)
		{
			que -> rear = (struct node*)malloc(sizeof(struct node));
			*(que -> rear) = *predefin;
			que -> rear -> next = NULL;
			que -> top = que -> rear;
		}
		else
		{
			que -> rear -> next = (struct node*)malloc(sizeof(struct node));
			que -> rear = que -> rear -> next;
			*(que -> rear) = *predefin;
			que -> rear -> next = NULL;
		}
	}
	}
	
	void del(struct Queue *que, struct node *deleted)
	{
	if(que -> top == NULL)
		printf("\nList is empty!!!");
	
	else
	{
		struct node *temp = que -> top;
		que -> top = que -> top -> next;
		temp -> next = NULL;
		*deleted = *temp;
		free(temp);
	
		if(que -> top == NULL)
			que -> rear = NULL;
	}
	}
	
	/*void copy(struct Queue *que2, struct Queue *que1)
	{
	if(que1 -> top == NULL)
		printf("\nList is empty!!!");
	
	else
	{
		struct node *list = que1 -> top;
		while(list)
		{
			insert(que2,list);
			list = list -> next;
		}
	}
	}
	
	void displayq(struct Queue que)
	{
	if(que.top == NULL)
		printf("\nList is empty!!!");
	
	else
	{
		struct node *list = que.top;
		while(list)
		{
			showdata(list);
			printf("\t");
			list = list -> next;
		}
	}
	}*/
	#endif


	
