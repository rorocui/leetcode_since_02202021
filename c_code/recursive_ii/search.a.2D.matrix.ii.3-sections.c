
bool searchMatrixThreeSections(int** matrix, int row_start, int row_end, int col_start, int col_end, int target)
{
    int pivot_row;
    int pivot_col;
    
    //printf("%d,%d,%d,%d\n", row_start, row_end, col_start, col_end);
    pivot_row = (row_end - row_start + 1) / 2;
    pivot_col = (col_end - col_start + 1) / 2;
    //printf("[%d,%d]\n", pivot_row, pivot_col);
    if(matrix[row_start + pivot_row][col_start + pivot_col] == target)
        return true;
    else if(matrix[row_start + pivot_row][col_start + pivot_col] > target)
    {
        /* Top left section */
        if(row_start + pivot_row - 1 >= row_start &&
            col_start + pivot_col - 1 >= col_start &&
            searchMatrixThreeSections(matrix, row_start, row_start + pivot_row - 1, col_start, col_start + pivot_col - 1, target))
            return true;
        /* Top right section */
        if(row_start + pivot_row - 1 >= row_start &&
            searchMatrixThreeSections(matrix, row_start, row_start + pivot_row - 1, col_start + pivot_col, col_end, target))
            return true;
        /* Bottom left section */
        if(col_start + pivot_col - 1 >= col_start &&
            searchMatrixThreeSections(matrix, row_start + pivot_row, row_end, col_start, col_start + pivot_col - 1, target))
            return true;
    }
    else
    {
        /* Bottom right section */
        if(row_start + pivot_row + 1 <= row_end &&
            col_start + pivot_col + 1 <= col_end &&
            searchMatrixThreeSections(matrix, row_start + pivot_row + 1, row_end, col_start + pivot_col + 1, col_end, target))
            return true;
        /* Top right section */
        if(col_start + pivot_col + 1 <= col_end &&
            searchMatrixThreeSections(matrix, row_start, row_start + pivot_row, col_start + pivot_col + 1, col_end, target))
            return true;
        /* Bottom left section */
        if(row_start + pivot_row + 1 <= row_end &&
            searchMatrixThreeSections(matrix, row_start + pivot_row + 1, row_end, col_start, col_start + pivot_col, target))
            return true;
    }

    return false;
}




bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target)
{
    return searchMatrixThreeSections(matrix, 0, matrixSize - 1, 0, *matrixColSize - 1, target);
}

/* 129 - 289ms(<27%) - 9.2MB, on Aug 31st, 2021 */
