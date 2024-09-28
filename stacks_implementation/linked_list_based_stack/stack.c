#include "stack.h"
#include <stdio.h>

// Creates a new empty stack on the heap
stack* create_stack(){
  stack *stk = malloc(sizeof(stack));
  stk->stack_size = 0;
  stk->top = NULL;
  return stk;
}

// Destroys the stack, and frees up its memory
void destroy_stack(stack *stk){
  node *nextNode = stk->top;
  while(nextNode != NULL){
    node *temp = nextNode->link;
    free(nextNode);
    nextNode = temp;
  }
  free(stk);
}

// Adds the value val to the top of the stack
void push(stack *stk, int val){
  stk->stack_size++;
  node *newNode = malloc(sizeof(node));
  newNode->value = val;
  if(stk->stack_size <= 0){
    stk->top = newNode;
    return;
  }
  newNode->link = stk->top;
  stk->top = newNode;
  
}

// Removes and returns the topmost item of the stack
int pop(stack *stk){
  if(stk->stack_size <= 0){
    return -1;
  }
  stk->stack_size--;
  int val = stk->top->value;
  node *temp = stk->top;
  stk->top = stk->top->link;
  free(temp);
  return val;
}

// Returns the topmost item of the stack, without changing the stack
int peek_top(stack *stk){
  if(stk->stack_size <= 0){
    return -1;
  }
  return stk->top->value;
}

// Returns the number of items on the stack
size_t stack_size(stack *stk){
  return stk->stack_size;
}

// Removes all of the items from the stack
void clear_stack(stack *stk){
  while(stk->top != NULL){
    node *temp = stk->top;
    stk->top = stk->top->link;
    free(temp);
  }
  stk->stack_size = 0;
}

// Outputs the items in the stack to the console window
void print_stack(stack *stk){
  node *nextNode = stk->top;
  while(nextNode != NULL){
    printf("%i ", nextNode->value);
    nextNode = nextNode->link;
  }
  printf("\n");
}