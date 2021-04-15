#include <stdio.h>
 
void main()
{
    #if DEBUG == 1  
       printf("Debug run\n");
    #else
       printf("Release run\n");
    #endif
}

