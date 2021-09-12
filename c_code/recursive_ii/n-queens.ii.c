void place_queen(int** matrix, int row, int col, int size, int queen_idx)
{
    int i, j;

    /* one row and one column */
    for(i = 0; i < size; i++)
    {
        if(matrix[row][i] == 0)
            matrix[row][i] = queen_idx;
        if(matrix[i][col] == 0)
            matrix[i][col] = queen_idx;
    }
    /* dale diagonal down */
    for(i = row + 1, j = col + 1; i < size && j < size; i++,j++)
        if(matrix[i][j] == 0) matrix[i][j] = queen_idx;
    /* hill diagonal down */
    for(i = row - 1, j = col - 1; i >= 0 && j >= 0; i--,j--)
        if(matrix[i][j] == 0) matrix[i][j] = queen_idx;
    /* dale diagonal up */
    for(i = row - 1, j = col + 1; i >= 0 && j < size; i--,j++)
        if(matrix[i][j] == 0) matrix[i][j] = queen_idx;
    /* hill diagonal up */
    for(i = row + 1, j = col - 1; i < size && j >= 0; i++,j--)
        if(matrix[i][j] == 0) matrix[i][j] = queen_idx;
}

void clear_matrix(int** matrix, int size)
{
    int i, j;

    for(i = 0; i < size; i++)
        for(j = 0; j < size; j++)
            matrix[i][j] = 0;
}

void remove_queen(int** matrix, int size, int queen_idx)
{
    int i, j;
    for(i = 0; i < size; i++) 
        for(j = 0; j < size; j++)
            if(matrix[i][j] == queen_idx) matrix[i][j] = 0;
}

int backtrack_nqueen(int** matrix, int size, int row, int count, int queen_idx)
{
    int col;
    int pre_count = count;
    //printf("### %#x:row=%d, count=%d\n", matrix, row, count);
    
    for(col = 0; col < size; col++)
    {
        if(row == 0) clear_matrix(matrix, size);
        
        if(matrix[row][col] == 0)
        {
            ////printf("found place to queen [%d][%d]=%d\n", row, col, matrix[row][col]);
            //printf("found place to queen [%d][%d]\n", row, col);
            //print_matrix(matrix, size);
            place_queen(matrix, row, col, size, queen_idx);
            //print_matrix(matrix, size);
            if(row + 1 == size)
            {
                count++;
                //printf("found one, count=%d\n", count);
            }
            else
                count = backtrack_nqueen(matrix, size, row + 1, count, queen_idx + 1);
            remove_queen(matrix, size, queen_idx);
            //printf("backtracking, row=%d\n", row + 1);
            /*
            if(pre_count == count || (col != size - 1 && row > 0))
            {
                //printf("backtracking, row=%d\n", row + 1);
                remove_queen(matrix, size, queen_idx);
            }
            pre_count = count;
            */
        }
        //else
            //printf("matrix[%d][%d] is 1\n", row, col);
    }
    ////printf("*** return\n");
    return count;
}

void print_matrix(int** matrix, int size)
{
    int i, j;
    for(i = 0; i < size; i++)
    {
        printf("[");
        for(j = 0; j < size; j++)
            printf("%d ", matrix[i][j]);
        printf("]\n");
    }
    printf("\n");
}

int totalNQueens(int n)
{
    int** new = NULL;
    int i;
    int count = 0;

    new = (int**)malloc(n * sizeof(int*));
    for(i = 0; i < n; i++)
        new[i] = (int*)calloc(n, sizeof(int));

    count = backtrack_nqueen(new, n, 0, 0, 1);

    for(i = 0; i < n; i++)
        free(new[i]);
    free(new);

    return count; 
}
/* 9 - 5ms(<13%) - 5.8MB, on Sep 11th, 2021 */
