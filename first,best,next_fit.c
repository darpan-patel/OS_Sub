#include<stdio.h>
	
void main()
{
	int p[10],b[10],ch,c[10],d[10],alloc[10],flag[10];
	int i,j,mem,proc,iChoice;
	
	printf("\nEnter the number of Process: ");
	scanf("%d",&proc);
	
	printf("\nEnter the number of Memory Blocks: ");
	scanf("%d",&mem);
	
	printf("\nEnter the size of each Process: ");
	for(i=0;i<proc;i++)
	{
		printf("\nProcess %d:",i+1);
		scanf("%d",&p[i]);
	}
	
	printf("\nEnter the size of each Memory Block:");
	for(j=0;j<mem;j++)
	{
		printf("\nBlock %d:",j+1);
		scanf("%d",&b[j]);c[j]=b[j];d[j]=b[j];
	}
	
	if(proc>=mem)
	{
		printf("\nThe number of processes are more than the available memory size. Please try again..\n\n");
		return;
	}
	else
	{	
		printf("\nSelect any one of the following:");
		printf("\n1.First fit \n2.Best fit \n3.Worst fit");
		printf("\nEnter your choice: ");
		scanf("%d",&ch);
	
		switch(ch)
		{
			case 1: //First Fit
			printf("\n*****First Fit Results*****\n");
			for(i=0;i<proc;i++)
			{
				for(j=0;j<mem;j++)
				{
					if(p[i]<=b[j])
					{
						alloc[j]=p[i];printf("\n\nAllocating process Id: %d",alloc[j]);
						printf("\n\nProcess Id: %d having Size: %d is allocated to the Memory Block:%d of size:%d.",i+1,p[i],j+1,b[j]);
						flag[i]=0,b[j]=0;
						break;
					}
					else flag[i]=1;
				}
			}
			for(i=0;i<proc;i++)
			{
				if(flag[i]!=0)
				printf("\n\nProcess Id:%d of Size: %d cannot be allocated.",i,p[i]);
			}
			break;
	
			case 2: //Best Fit
			printf("\n*****Best Fit Results*****\n");
			for(i=0;i<mem;i++)
			{
				for(j=i+1;j<mem;j++)
				{
					if(c[i]>c[j])
					{
						int temp=c[i];c[i]=c[j];c[j]=temp;
					}
				}
			}
	
			for(i=0;i<proc;i++)
			{
				for(j=0;j<mem;j++)
				{
					if(p[i]<=c[j])
					{
						alloc[j]=p[i];printf("\n\nAllocating process Id: %d",alloc[j]);
						printf("Process Id: %d having Size: %d is allocated to the Memory Block:%d of size:%d.",i+1,p[i],j+1,c[j]);
						flag[i]=0,c[j]=0;
						break;
					}
					else
						flag[i]=1;
				}
			}
			for(i=0;i<proc;i++)
			{
				if(flag[i]!=0)
				printf("\n\nProcess Id:%d of Size: %d cannot be allocated.",i,p[i]);
			}
			break;
	
			case 3: //Worst Fit
			printf("\n*****Worst Fit Results*****\n");
			for(i=0;i<mem;i++)
			{
				for(j=i+1;j<mem;j++)
				{
					if(d[i]<d[j])
					{
						int temp=d[i];d[i]=d[j];d[j]=temp;
					}
				}
			}
	
			for(i=0;i<proc;i++)
			{
				for(j=0;j<mem;j++)
				{
					if(p[i]<=d[j])
					{
						alloc[j]=p[i];
						printf("\n\nAllocating process Id: %d",alloc[j]);
						printf("\n\nProcess Id: %d having Size: %d is allocated to the Memory Block:%d of size:%d.",i+1,p[i],j+1,d[j]);
						flag[i]=0,d[j]=0;
						break;
					}
					else flag[i]=1;
				}
			}
			for(i=0;i<proc;i++)
			{
				if(flag[i]!=0)
				printf("\n\nProcess Id:%d of Size: %d cannot be allocated.",i,p[i]);
			}
	
			break;
		}
	}
}
