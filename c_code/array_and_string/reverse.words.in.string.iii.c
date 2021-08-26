char * reverseWords(char * s)
{
    int i, j;
    int start, end;
    int len;
    int idx;
    char* ret = NULL;

    len = strlen(s);
    printf("len=%d\n", len);
    ret = (char*)calloc(len + 1, sizeof(char));
    idx = start = end = 0;

    while(end < len)
    {
	    while(end < len && s[end] != 0x20)
	        end++;
        //printf("start=%d, end=%d\n", start, end);
        //printf("%c,%c\n", ret[idx], s[4]);
	    for(i = end - 1; i >= start; i--)
        {
	        ret[idx++] = s[i];
            //printf("%c,[%d]%c\n", ret[idx], i, s[i]);
        }
        //printf("2:start=%d, end=%d\n", start, end);
	    if(end < len)
        {
	        ret[idx++] = 0x20;
            end++;
            start = end;
        }
    }
    //printf("idx=%d\n", idx);
    ret[idx] = 0;

    return ret;
}
/* 29 - 4(<95%) - 7.6MB, on Aug 25th, 2021 */
