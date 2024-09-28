#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "stack.h" 

stack* create_stack() {
    size_t capacity = 10;
    stack* myStack = (stack*)malloc(sizeof(stack)); 
    if (myStack != NULL) { 
        myStack->stack_size = 0;
        myStack->array_size = capacity;
        myStack->values = malloc(capacity * sizeof(int));
    }
    return myStack;
}

// Destroys the stack, and frees up its memory
void destroy_stack(stack *stk) {
    if (stk != NULL) {
        free(stk->values); // Free the array of values
        free(stk);         // Free the stack structure
    }
}

// Adds the value val to the top of the stack
void push(stack *stk, int val) {
    stk->stack_size++;
    if (stk->stack_size >= stk->array_size) {
        size_t temp = stk->array_size * 2;
        int *new_arr = realloc(stk->values, temp * sizeof(int));

        stk->values = new_arr;
        stk->array_size = temp;
    }
}

// Removes and returns the topmost item of the stack
int pop(stack *stk) {
    if (stk->stack_size > 0) {
        stk->stack_size--;
        return stk->values[stk->stack_size];
    }
}

// Returns the topmost item of the stack, without changing the stack
int peek_top(stack *stk) {
    if (stk->stack_size > 0) {
        return stk->values[(stk->stack_size)-1];
    }
}

// Returns the number of items on the stack
size_t stack_size(stack *stk) {
    return stk->stack_size;
}

// Removes all of the items from the stack
void clear_stack(stack *stk) {
    size_t temp = stk->array_size * 2;
    int *new_arr = realloc(stk->values, temp * sizeof(int));

    stk->values = new_arr;
    stk->array_size = temp;
}

// Outputs the items in the stack to the console window
void print_stack(stack *stk);