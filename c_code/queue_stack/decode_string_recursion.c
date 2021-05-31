
char* decodeRepeatString(char *s, char *out, int *retSize)
{
    int repeat = 0;
    int repeat_size = 0;
    int m, n;
    int ret = 0, size = 0;
    char* ptr;


    ptr = s;
    while(0x30 <= *ptr && *ptr <= 0x39)
    {
        repeat = repeat * 10 + (int)(*ptr - 0x30);
        ptr++;
    }
    ptr++;
    //printf("repeat=%d\n",repeat);
    while(*ptr != 0x5D) /* 0x5D = ']' */
    {
        //printf("%c\n", *ptr);
        if( 0x61 <= *ptr && *ptr <= 0x7A)
        {
            //printf("%c-%d\n", *ptr, ret);
            out[ret++] = *ptr;
        }
        else if(0x31 <= *ptr && *ptr <= 0x39)
        {
            ptr = decodeRepeatString(ptr, out + ret, &size);
            //printf("recursion size =%d\n",size);
            ret += size;
        }
        else
            printf("wrong charactor\n");
        ptr++;
    }

    /* repeat string is ready, process it and output to *out */
    repeat_size = ret;
    //printf("repeat_size = %d\n", repeat_size);
    for(m = 1; m < repeat; m++)
        for(n = 0; n < repeat_size; n++)
        {
            out[ret++] = out[n];
        }

    //printf("ret = %d\n", ret);
    *retSize = ret;
    return ptr;

}

#define MAX_SIZE 2000

char * decodeString(char * s)
{

    char* new  = NULL;
    char* ptr = NULL;
    int i = 0;
    int ret = 0, size = 0;

    new = (char*)calloc(MAX_SIZE, sizeof(char));

    ptr = s;
    while(*ptr != '\0')
    {
        if( 0x61 <= *ptr && *ptr <= 0x7A)
        {
            new[ret++] = *ptr;
        }
        else if(0x31 <= *ptr && *ptr <= 0x39)
        {
            ptr = decodeRepeatString(ptr, new + ret, &size);
            ret += size;
        }
        else
            printf("wrong charactor\n");
        ptr++;
    }


    return new;

}
/* 34 tests case in 0ms(<100%), in 5.8MB on May 22th, 2021*/
