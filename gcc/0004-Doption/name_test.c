#include <stdio.h>
 
void main()
{
    #ifdef DEBUG   
       printf("Debug run\n");
    #else
       printf("Release run\n");
    #endif
}
