
static int g_index;

int cal_combinations(int n, int k)
{
    int i;
    unsigned long long temp = 1;

    for(i = n; i > k; i--)
        temp *= i; 
    for(i = 1; i <= n - k; i++)
        temp /= i;

    return (int)temp;
}

/* Start from m to n, and k digits combinations. */
void combine_backtrack(int m, int n, int k, int idx, int size, int** ret)
{
    int i, j;

    //printf("m=%d,n=%d,k=%d,idx=%d,ret=%#x,g_index=%d\n", m, n, k, idx, ret, g_index);
    for(i = m; i <= n && g_index < size; i++)
    {
        //printf("g_index=%d\n", g_index);
        ////printf("searching[idx=%d]... ", idx);
        for(j = 0; j < idx; j++)
        {
            ////printf("%d.", ret[g_index][j]);
            if(ret[g_index][j] == i) break;
        }
        ////printf("\n");
        ////printf("[%d] ? ret[%d][%d]=%d\n", i, g_index, j, ret[g_index][j]);
        if(j == idx)
        {
            ret[g_index][j] = i;
	        if(idx < k - 1)
	            combine_backtrack(i, n, k, idx + 1, size, ret);
	        else
	        {
                /* Copy the current array to next possible answer */
                //printf("%d:[", g_index);
	            for(j = 0; j < k; j++)
                    //printf("%d.", ret[g_index][j]);
                //printf("]\n");
                if(g_index < size - 1)
                {
	                for(j = 0; j < idx; j++)
	                    ret[g_index + 1][j] = ret[g_index][j];
                }
	            g_index++;
	        }
        }
    }
    //printf("return idx=%d\n\n", idx);
}


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combine(int n, int k, int* returnSize, int** returnColumnSizes)
{
    int i, j;
    int** ret;

    g_index = 0;
    *returnSize = cal_combinations(n, k);
    //printf("returnSize=%d\n", *returnSize);
    *returnColumnSizes = (int*)calloc(*returnSize, sizeof(int));
    ret = (int**)calloc(*returnSize, sizeof(int*));
    for(i = 0; i < *returnSize; i++)
    {
        ret[i] = (int*)calloc(k, sizeof(int));
        (*returnColumnSizes)[i] = k;
    }

    combine_backtrack(1, n, k, 0, *returnSize, ret);

    //printf("ret=%#x\n", ret);
    return ret;
}
/* 27 - 92(<29%) - 13.2 MB, on Sep 28th, 2021 */
