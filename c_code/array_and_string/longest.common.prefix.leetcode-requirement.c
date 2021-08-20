char * longestCommonPrefix(char ** strs, int strsSize)
{
    int     i, j;
    int     min_len;
    int     min_idx;
    int*    len = NULL;
    int     prefix_len;
    char*   new = NULL;
    char*   ret = NULL;
    bool    find_prefix = true;
    

    len = (int*)calloc(strsSize, sizeof(int));

    prefix_len = 0;
    min_len = min_idx = 200;
    for(i = 0; i < strsSize; i++)
    {
        len[i] = strlen(strs[i]);
        if(len[i] < min_len)
        {
            min_len = len[i];
            min_idx = i;
        }
    }
    new = (char*)calloc(min_len + 1, sizeof(char));
    ret = (char*)calloc(min_len + 1, sizeof(char));
    memset(ret, 0, min_len + 1);
    for(i = 0; i < min_len; i++)
    {
        prefix_len++;
        memset(new, 0, min_len + 1);
        strncpy(new, &strs[min_idx][0], prefix_len);
        for(j = 0; j < strsSize; j++)
        {
            if(j != min_idx && strncmp(strs[j], new, prefix_len))
            {
                find_prefix = false;
                break;
            }
            else
                find_prefix = true;
        }
        if(! find_prefix) /* Complete the search quit for i loop */
            break;
        if(j == strsSize && find_prefix && prefix_len >= strlen(ret))
        {
            memset(ret, 0, min_len + 1);
            strcpy(ret, new);
        }
    }
    free(new);

    return ret;
}

/* 123 - 4(<43%) - 5.8, on Aug 19th, 2021 */
