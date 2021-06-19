#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

void main()
{
        printf("%s\n", __func__);
    char a[20] = "test program";
    printf("%d\n", (int)strlen(a));
    char* test=(char*)malloc(10*sizeof(char));
    printf("%d\n", (int)strlen(test));
    for(int m = 0; m < 10; m++) test[m] = 0xFF;
    printf("%d\n", (int)strlen(test));
    free(test);
    test = calloc(10, sizeof(char));
    printf("%d\n", (int)strlen(test));
    for(int m = 0; m < 10; m++) test[m] = 0x7F;
    printf("%d\n", (int)strlen(test));

}
