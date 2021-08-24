/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getRow(int rowIndex, int* returnSize)
{
    int* ret = NULL;
    int i, j;

    ret  = (int*)calloc(rowIndex + 1, sizeof(int));
    *returnSize = rowIndex + 1;

    for(i = 0; i <= rowIndex; i++)
    {
        ret[rowIndex - i] = 1;
        for(j = rowIndex - i + 1; j < rowIndex; j++)
        {
            ret[j] = ret[j] + ret[j + 1];
            
        }
        ret[rowIndex] = 1;
    }

    return ret;
}

/* 34 - 0ms - 5.9MB, on Aug 23rd, 2021 */
