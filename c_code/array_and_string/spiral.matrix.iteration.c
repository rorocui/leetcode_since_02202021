void matrix_boundary_travere(int** matrix, int row_len, int col_len, int* ret)
{
    int i, j, idx;
    int row_min, row_max, col_min, col_max;

    idx = row_min = col_min = 0;
    row_max = row_len;
    col_max = col_len;
    while(row_min < (row_max - 1) && col_min < (col_max - 1))
    {
        for(j = col_min; j < col_max - 1; j++) 
            ret[idx++] = matrix[col_min][j];
        for(i = row_min; i < row_max - 1; i++) 
            ret[idx++] = matrix[i][col_max - 1];
        for(j = col_max - 1; j > col_min; j--) 
            ret[idx++] = matrix[row_max -1][j];
        for(i = row_max - 1; i > row_min; i--) 
            ret[idx++] = matrix[i][row_min];
        row_max--;
        row_min++;
        col_max--;
        col_min++;
    }
    if(row_max - row_min == 1)
    {
        for(j = col_min; j < col_max; j++)
            ret[idx++] = matrix[row_min][j];
    }    
    else if(col_max - row_min == 1)
    {
        for(i = row_min; i < row_max; i++)
            ret[idx++] = matrix[i][col_min];
    }    

}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize)
{
    int* new = NULL;

    *returnSize = matrixSize * matrixColSize[0];

    new = (int*)calloc(*returnSize, sizeof(int));

    matrix_boundary_travere(matrix, matrixSize, matrixColSize[0], new);

    return new;
}

/* 23 - 0(<100%) - 5.9MB, Aug 12th, 2021 */
