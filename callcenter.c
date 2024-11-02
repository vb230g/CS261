#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "queue.h"
#include "stack.h"


struct cc {
	int ID;
	char* name;
	char* reason;
};

void add_caller(int *calls, struct queue* ccqueue);
void make_call(int *calls, int *answered, struct stack* ccstack, struct queue* ccqueue);
void display_call_stack(struct stack* ccstack, int answered);
void display_call_queue(struct queue* ccqueue, int calls);

int main(int argc, char const *argv[]) {
	struct stack* ccstack = stack_create();
	struct queue* ccqueue = queue_create();
	bool go = true;
	int calls = 0;
	int answered = 0;
	do{	   
	   printf("1. Receive a new call\n"
"2. Answer a call\n"
"3. Current state of the stack – answered calls\n"
"4. Current state of the queue – calls to be answered\n"
"5. Quit\n");
	   int x;
	   printf("choose an option\n");
	   scanf("%d",&x);
	   if(x==1) {
		   add_caller(&calls, ccqueue);
	   }
	   else if(x==2) {
		   make_call(&calls, &answered,  ccstack, ccqueue);
	   }

	   else if(x==3) {
		   display_call_stack(ccstack, answered);
	   }
	   else if(x==4) {
		display_call_queue(ccqueue, calls);
	   }
	   else if(x==5) {// freeing function
		while (!stack_isempty(ccstack)) {// freeing everything in the stack
                struct cc* answered_caller = stack_pop(ccstack);
                free(answered_caller->name);
                free(answered_caller->reason);
                free(answered_caller);
            	}
            	while (!queue_isempty(ccqueue)) {//freeing everything in the queue
                struct cc* waiting_caller = queue_dequeue(ccqueue);
                free(waiting_caller->name);
                free(waiting_caller->reason);
                free(waiting_caller);
            	}
		   stack_free(ccstack);// freeing the stack
                   queue_free(ccqueue);//freeing the queue
		   go = !go;
	   }

	}while(go);
	return 0;
}






void add_caller(int *calls, struct queue* ccqueue) {// this takes input from the caller as to what their information is and enqueues it
	struct cc* caller = (struct cc*)malloc(sizeof(struct cc));
                   caller->name = (char*)malloc(100 * sizeof(char));
                   caller->reason = (char*)malloc(100 * sizeof(char));
                   printf("please give a caller name, ID and reason\n");
                   printf("Caller Name: ");
                   scanf("%s",caller->name);
                   printf("Caller Id: ");
                   scanf("%d",&caller->ID);
                   printf("Caller Reason: ");
                   scanf("%s",caller->reason);
                   queue_enqueue(ccqueue,caller);
                   printf("the call has bee successfully added to the queue\n");
                   (*calls)++;

}

void make_call(int *calls, int *answered, struct stack* ccstack, struct queue* ccqueue) {// this function dequeues a caller from the back and pushes it to the stack
		   if(calls>0) {
                   struct cc* CALLER = queue_front(ccqueue);
                   stack_push(ccstack, queue_dequeue(ccqueue));
                   printf("The following call has been answered and added to the stack: \n" "Call Id: %d\n" "Caller's Name: %s\n" "Call Reason %s\n",CALLER->ID, CALLER->name, CALLER->reason);
                   (*calls)--;
                   (*answered)++;
                   } else {
                           printf("there are no more calls needed to be made\n");
                   }
}

void display_call_stack(struct stack* ccstack, int answered) {// this function displays what is in the ccstack and prints out what is on the top
		if(answered!=0) {
                struct cc* CALLER = stack_top(ccstack);
                printf("calls answered: %d\n" "last caller: name: %s\n" "ID: %d\n " "reason: %s\n", answered, CALLER->name, CALLER->ID, CALLER->reason);
                } else {
                printf("0 calls have been answered\n");
                }
}

void display_call_queue(struct queue* ccqueue, int calls) {// this function displays the queue and pritns out the next caller
		if(calls!=0) {
                struct cc* CALLER = queue_front(ccqueue);
                printf("calls to be answered: %d\n" "next caller: name: %s\n" "ID: %d\n " "reason: %s\n", calls, CALLER->name, CALLER->ID, CALLER->reason);
                } else {
                printf("No more calls need to be answered at the moment\n");
                }
}
