#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

void main()
{
    for(int i = 1; i <= 9; i++)
        for(int j = 1; j <= 9; j++)
        {
            if( 0 <= i && i <= 2)
                printf("[%d][%d]->%d\n", i, j, i * j + j);
        }

}
