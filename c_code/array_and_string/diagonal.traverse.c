/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDiagonalOrder(int** mat, int matSize, int* matColSize, int* returnSize)
{
    int diagonal_idx_max; 
    int diagonal_idx;
    int idx;
    int row_i;
    int row, col;
    int* new = NULL;
    bool row_first = false;

    idx = 0;
    row = matSize;
    col = matColSize[0];
    new = (int*)calloc(row * col, sizeof(int));
    //printf("row %d,col %d\n", row, col);
    diagonal_idx_max = (row - 1) + (col - 1);

    for(diagonal_idx = 0; diagonal_idx <= diagonal_idx_max; diagonal_idx++)
    {
        if(row_first)
        {
            for(row_i = 0; row_i < row && row_i <= diagonal_idx; row_i++)
            {
                //printf("r:row_i=%d\n", row_i);
                if((diagonal_idx - row_i) >= 0 && (diagonal_idx - row_i) < col)
                {
                    //printf("r:row_i-%d,diagonal_idx-%d,idx-%d\n", row_i, diagonal_idx, idx);
                    new[idx++] = mat[row_i][diagonal_idx - row_i];
                }
            }
            row_first = false;
        }
        else
        {
            row_i = (diagonal_idx > (row - 1)) ? row - 1 : diagonal_idx;
            //printf("c-out-for:row_i-%d,diagonal_idx-%d,idx-%d\n", row_i, diagonal_idx, idx);
            for(row_i; row_i >= 0; row_i--)
            {
                if((diagonal_idx - row_i) >= 0 && (diagonal_idx - row_i) < col)
                {
                    //printf("c:row_i-%d,diagonal_idx-%d,idx-%d\n", row_i, diagonal_idx, idx);
                    new[idx++] = mat[row_i][diagonal_idx - row_i];
                }
            }
            row_first = true;
        }
    }

    *returnSize = idx;

    return new;
}

/* 32 - 96(<27%) - 14.5MB, Aug 11th, 2021 */
