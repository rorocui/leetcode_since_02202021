void reverseString(char* s)
{
    int i, j;
    char temp;

    i = 0;
    j = strlen(s) - 1;

    while(i < j)
    {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i++;
        j--;
    }
}

char * reverseWords(char * s)
{
    int start, end;
    char temp;
    int len;
    int i, j;
    int idx = 0;

    reverseString(s);
    start = 0;
    len = strlen(s);
    //printf("len=%d,%s\n", len, s);
    while(s[start] == 0x20)
        start++;
    ////printf("1:start=%d,end=%d\n", start, end);
    for(end = start; end <= len; end++)
    {
        while(end < len && s[end] != 0x20)
            end++;
        //printf("2:start=%d,end=%d\n", start, end);
        if(start <= end - 1)
        {
            i = start;
            j = end - 1;
            while(i < j)
            {
                temp = s[i];
                s[i++] = s[j];
                s[j--] = temp;
            }
            //printf("2.5: %s\n", s);
            if(idx < start)
            {
                //printf("idx=%d, start=%d, end=%d\n", idx, start, end);
                for(i = start; i < end; i++)
                {
                    s[idx++] = s[i];
                    s[i] = 0x20;
                }
                //printf("a:idx=%d,start=%d\n", idx, start);
            }
            else
                idx = end;
        }
        //printf("2.6:%s\n", s);
        //printf("3:start=%d,end=%d\n", start, end);
        while(end < len && s[end] ==0x20)
            end++;
        if(end < len)
            s[idx++] = 0x20;
        start = end;
        
        //printf("4:start=%d,end=%d\n", start, end);
    }
    //printf("5:start=%d,end=%d\n", start, end);
    s[idx] = 0;
    
    //printf("%s\n", s);
    return s;
}

/* O(1) 57 - 0(<100%) - 6.3MB, on Aug 25th, 2021 */
