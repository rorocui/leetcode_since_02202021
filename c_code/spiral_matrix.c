
void matrix_boundary_travere(int** matrix, int row_len, int col_len, int* ret)
{
    int i, j, idx;

    if(row_len == 1)
    {
        for(j = 0; j < col_len; j++)
            ret[j] = matrix[0][j];
        return;
    }
    if(col_len == 1)
    {
        for(i = 0; i < row_len; i++)
            ret[i] = matrix[i][0];
        return;
    }
    idx = 0;

    for(j = 0; j < col_len - 1; j++) 
        ret[idx++] = matrix[0][j];
    for(i = 0; i < row_len - 1; i++) 
        ret[idx++] = matrix[i][col_len - 1];
    for(j = col_len - 1; j > 0; j--) 
        ret[idx++] = matrix[row_len -1 ][j];
    for(i = row_len - 1; i > 0; i--) 
        ret[idx++] = matrix[i][0];

    matrix_boundary_travere(int** &matrix[1][1], row_len - 1, col_len, ret + idx);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize)
{
    int* new = NULL;

    *returnSize = matrixSize * matrixColSize[0];

    new = (int*)collac(*returnSize, sizeof(int));

    matrix_boundary_travere(matrix, matrixSize, matrixColSize[0], new);

    return new;
}
