#include <sys/time.h> 
#include <stdio.h>
#include "stack.h" 

int main() {
    struct timeval tv1, tv2;
    stack *stk = create_stack();

    gettimeofday(&tv1, NULL);

    for(int i = 0; i < 15000000; ++i)
        push(stk, 5);
    
    
    gettimeofday(&tv2, NULL);
    printf("Total time = %f seconds\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));

    return 0;
}