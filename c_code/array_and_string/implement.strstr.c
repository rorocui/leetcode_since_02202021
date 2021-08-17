int strStr(char * haystack, char * needle)
{
    int size_h, size_n;
    int i, j;
    bool match = false;

    size_h = strlen(haystack);
    size_n = strlen(needle);
    if(size_n == 0) return 0;
    if(size_h < size_n) return -1;
    for(i = 0; i <= (size_h - size_n); i++)
    {
        for(j = 0; j < size_n; j++)
        {
            if(haystack[i + j] != needle[j]) break;
            if(j == (size_n - 1) && haystack[i + j] == needle[j]) match = true;
        }
        if(match) return i;
    }

    return -1;
}

/* 80 920(<39%) - 6.4MB, on Aug 16th, 2021 */
