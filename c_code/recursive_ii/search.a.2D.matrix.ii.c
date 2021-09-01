bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target)
{
    int pivot_row;
    int *pivot_col;

    
    pivot_row = matrixSize / 2;
    *pivot_col = *matrixSize / 2;
    if(matrix[pivot_row][*pivol_col] == target)
        return true;
    else if(matrix[pivot_row][*pivol_col] > target)
    {
        while(pivot_row > 1 && matrix[pivot_row - 1][*pivot_col] > target)
            pivot_row--;
        if(matrix[pivot_row][*pivol_col] == target)
            return true;
        else
        {
            if(searchMatrix(&matrix[pivot_row][0], matrixSize - pivot_row, pivot_col, target))
                return true;
            *pivot_col = *matrixColSize - *pivot_col;
            if(searchMatrix(&matrix[0][*pivot_col], pivot_row + 1, pivot_col, target))
                return true;
        }
    }
    else
    {
        while(pivot_row < matrixSize && matrix[pivot_row + 1][*pivot_col] < target)
            pivot_row++;
        if(matrix[pivot_row][*pivol_col] == target)
            return true;
        else
        {
            if(searchMatrix(&matrix[pivot_row][0], matrixSize - pivot_row, pivot_col, target))
                return true;
            *pivot_col = *matrixColSize - *pivot_col;
            if(searchMatrix(&matrix[0][*pivot_col], pivot_row + 1, pivot_col, target))
                return true;
        }
    }


    return false;
}
