/*******************Garbage Collection Header Files************************/
/*
	This header file allocates memory from heap. If heap memory is not 
	sufficient then it collects garbage and tries to reallocate the memory.
*/


/*
	This file is developed as a part of the Operating System project
				Author:-
					Darpan Patel
					Shreya Gokani

*/


/*************************INSTRUCTIONS**************************/
/*					

		=> This Headers file needs to be included in the folder
		        where you are writing your program.
		=>  Include this file in your program.
		=>  Define malloc=new_malloc
*/
/******************************************************************/



/*************************Header Files*****************************/

#include <signal.h>	//used to handle the signals while finding the stack address limit
#include <stdio.h>	//used for standard input & output
#include <stdlib.h>	//used to access function like malloc
#include <setjmp.h>	//set jump operation
#include <unistd.h>	//used to read values of enviornment varibales
#include <stddef.h>	//defines data type size_t
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef int BOOL;

/** Structure For Maintaining Record About Location, Pointer & Flags **/

typedef struct record
{
	void * heap_ptr; 	//address of the memory block thats getting allocated
	size_t size_allocated;		//size of the memory block pointed by heap ptr
	BOOL used;		//denoted whether memory pointed by heap ptr is referenced or not
	BOOL checked;		//for finding other live objects
	struct record * next;		//for linklist

}recording_block;  


/** Global Head Ptr Of record_block **/

extern int end,etext;
recording_block * head;
jmp_buf jmpbuff;
size_t max_heap = 640 * 1024 ;
size_t current_heap = 0;  

void checklimit( );
void recording_garbage();
void collect_collectables();
void record_keeping( void * gc_ptr , size_t gc_size );
void * find_stack_high_ptr();
void * GC_malloc( size_t gc_size );
BOOL search_in_addr_space( void * low_addr , void * high_addr , void * search_addr );
void sig( int val );

void recording_garbage()
{
	recording_block * prev , * current , * temp;
	
	prev = head;

	current = head->next;

	while( current != NULL ) 
	{
		if( current->used == FALSE )
		{
			
			temp = prev->next;
			prev->next = current->next;
			current = prev->next;
			
			temp -> heap_ptr = NULL ;
			temp -> used = -1;
			temp -> next = NULL ;
			temp -> size_allocated = 0;
			temp -> checked = -1;

			free(temp);
		}
		else
		{
			prev = prev->next;
			current = current->next;
		}
	}
}


void sig(int val)
{
	longjmp(jmpbuff,1);
}								 

void* find_stack_high_ptr()
{
	int *ptr,current,dereference;
	ptr=&current;
	if( setjmp(jmpbuff)!=0 )
	{
		return ptr-1;		
	}
	while(1)
	{
		ptr++;
		dereference=*ptr;
		if(signal(SIGBUS,sig)==SIG_ERR || signal(SIGSEGV,sig)==SIG_ERR )
		{ 
			fprintf(stderr,"\n\n\nFATAL ERROR ( IN MESSAGE PASSING USING SIGNALS ) WHILE TRYING TO GARBAGE COLLECT. GC ROUTINE IS EXITING . \n\n\n");
			exit(1);
		}
	}	   
  return ptr-1;
}				

BOOL search_in_addr_space(void * low_addr , void * high_addr , void * search_addr)
{
	void ** ptr_to_memory_ptr;
	void * unit_decrement;
	unit_decrement = high_addr;

	while( unit_decrement > low_addr )
	{
		unit_decrement--;
		ptr_to_memory_ptr = (void**)unit_decrement;
		if( (*ptr_to_memory_ptr) == search_addr )
			return TRUE;
	}

	return FALSE;	  
} 

void collect_collectables()
{ 
	recording_block * temp ;
	temp = head->next;
	while( temp != NULL) 
	{
		if( temp->used == FALSE ) 
		{
 			current_heap -= temp->size_allocated; 
			free(temp->heap_ptr);
		}
		temp = temp->next;
	}
	recording_garbage();
}

void * collect_garbage()
{
	static void * stack_high_ptr;
	void * stack_low_ptr;
        int stack_var;
        recording_block * temp;
        void *ptr;
        static int flag = 0; 
 
        stack_low_ptr = &stack_var;
        if(flag == 0)
        {

                stack_high_ptr = find_stack_high_ptr();
                flag = 1;
        }

        temp = head->next;
        while( temp != NULL )
        {
				temp->used = FALSE;
                temp->checked = FALSE;
                temp = temp->next;
    	}

        temp = head->next;

        while( temp != NULL )
        {
            temp->used = search_in_addr_space( stack_low_ptr ,stack_high_ptr , temp->heap_ptr);
			if( temp->used == FALSE )
                temp->used = search_in_addr_space(&etext , &end , temp->heap_ptr );
                temp = temp->next;

        }

        collect_collectables();   
        return;
}


void record_keeping(void * ptr , size_t size )
{
	recording_block * temp;
	if(head == NULL)
	{
		head = malloc(sizeof(recording_block));
		head->heap_ptr = NULL;
		head->used = TRUE;
		head->size_allocated = 0;
		head->next = NULL;
		head->checked = TRUE;
		
	}

	temp=malloc(sizeof(recording_block));
	temp->heap_ptr = ptr;
	temp->size_allocated = size;
	temp->used = FALSE;
	temp->checked = FALSE; 
	temp->next = head->next;
	head->next = temp;
	return;
}				 

void checklimit( )
{
	if( current_heap > max_heap )
    {
	    collect_garbage();
        current_heap =0;
    }
    return;
}   


void * new_malloc(size_t size)
{ 

	void * ptr;

	ptr=malloc(size);

	if(ptr!=NULL)
	{
		record_keeping(ptr,size);
		checklimit();
	}
	else
	{
		if(ptr == NULL)
		{
			printf("\nYour Request cannot be satisfied even after Garbage Collection \n");
			return NULL;		
		}
	}	
	current_heap += size;
	return ptr;
}
