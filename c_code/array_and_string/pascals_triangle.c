
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generate(int numRows, int* returnSize, int** returnColumnSizes)
{
    int** new = NULL;
    int i,j;

    new = (int**)malloc(numRows * sizeof(int*));
    *returnColumnSizes = (int*)calloc(numRows, sizeof(int));
    for(i = 0; i < numRows; i++)
    {
        new[i] = (int*)malloc((i + 1) * sizeof(int));
        (*returnColumnSizes)[i] = i + 1;
        new[i][0] = new[i][i] = 1;
    }
    for(i = 2; i < numRows; i++)
    {
        for(j = 1; j < (*returnColumnSizes)[i] - 1; j++)
        {
            new[i][j] = new[i - 1][j - 1] + new[i - 1][j];
            printf("%d,%d=%d\n", i, j, new[i][j]);
        }
    }

    *returnSize = numRows;

    return new;
}

/* 14 - 3(<18%) - 5.9, on aug 14th, 2021 */
