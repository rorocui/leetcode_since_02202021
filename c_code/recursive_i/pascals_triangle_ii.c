

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getRow(int rowIndex, int* returnSize){
    //printf("getRow: %d\n", rowIndex);
    int* sub_ret = NULL;
    int* ret;
    int i;

    ret = calloc(rowIndex + 1, sizeof(int));
    
    ret[0] = ret[rowIndex] = 1; 
    if(rowIndex >= 2)
    {
        sub_ret = getRow(rowIndex - 1, returnSize);
        //printf("0x%x-sub_ret[0]=%d\n", sub_ret, sub_ret[0]);
        for(i = 1; i < *returnSize; i++)
        {
            //printf("sub_ret[%d]=%d\n", i, sub_ret[i]);
            ret[i] = sub_ret[i - 1] + sub_ret[i];
            //printf("ret[%d]=%d\n", i, ret[i]);
        }
    }
    *returnSize = rowIndex + 1;
    
    if(sub_ret) free(sub_ret);
    return ret;
}
/* 34-0-6.2 on May 29th, 2021 */
