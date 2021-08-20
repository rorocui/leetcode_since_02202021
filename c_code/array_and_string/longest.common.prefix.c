/* I don't think the defination is clear, looks like that requires
 * common has start from first charater in all strings 
 * Keep this one as good solution to the question which common prefix could be 
 * in middle of any strings, on Aug 19th, 2021 */

char * longestCommonPrefix(char ** strs, int strsSize)
{
    int i, j;
    int min_len;
    int min_idx;
    int* len = NULL;
    int prefix_pre_idx, prefix_len;
    char* new = NULL;
    char* ret = NULL;
    bool find_prefix = true;
    

    len = (int*)calloc(strsSize, sizeof(int));

    prefix_pre_idx = prefix_len = 0;
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
    printf("min_len=%d,min_idx=%d\n", min_len, min_idx);
    for(i = 0; i < min_len; i++)
    {
        printf("b1:[%d]new=%s,ret=%s,pre_len=%d\n", i, new, ret, prefix_len);
        prefix_len++;
        printf("b2:[%d]new=%s,ret=%s,pre_len=%d\n", i, new, ret, prefix_len);
        memset(new, 0, min_len);
        strncpy(new, &strs[min_idx][prefix_pre_idx], prefix_len);
        printf("[%d]new=%s,ret=%s,len=%d\n", i, new, ret, prefix_len);
        for(j = 0; j < strsSize; j++)
        {
            if(j != min_idx && ! strstr(strs[j], new))
            {
                prefix_pre_idx++;
                i = prefix_pre_idx;
                prefix_len = 0;
                find_prefix = false;
                break;
            }
            else
                find_prefix = true;
        }
        printf("j:[%d]new=%s,ret=%s,find=%d,len-ret=%d\n", j, new, ret, find_prefix, strlen(ret));
        if(j == strsSize && find_prefix && prefix_len >= strlen(ret))
        {
            memset(ret, 0, min_len);
            strcpy(ret, new);
            ret[prefix_len] = 0;
            printf("inside j:[%d]new=%s,ret=%s,find=%d,len-ret=%d\n", j, new, ret, find_prefix, strlen(ret));
        }
        printf("j1:[%d]new=%s,ret=%s,find=%d,len-ret=%d\n", j, new, ret, find_prefix, strlen(ret));

    }
    free(new);

    printf("before ret\n");
    printf("before ret:%s\n", ret);
    printf("before ret:%d\n", strlen(ret));
    return ret;
}
