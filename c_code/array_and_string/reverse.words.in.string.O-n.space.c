
char * reverseWords(char * s)
{
    int len = 0;
    int end, start;
    int idx = 0;
    int i;
    char* ret;

    len = strlen(s);
    ret = (char*)calloc(len + 1, sizeof(char));

    end = start = len - 1;
    while(start >= 0 && s[start] == 0x20)
        start--;
    for(end = start; start >= -1; start--)
    {
        while(start >= 0 && s[start] != 0x20)
            start--;
        if(end >= start)
        {
            for(i = start + 1; i <= end; i++)
            {
                ret[idx++] = s[i];
            }
        }
        while(start >= 0 && s[start] == 0x20)
            start--;
        if(start >= 0)
        {
            ret[idx++] = 0x20;
            end = start;
        }
    }
    ret[len] = 0;

    return ret;
}

/* 57 - 0(<100%) - 6.3MB, on Aug 23rd, 2021 */

