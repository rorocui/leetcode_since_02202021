bool searchMatrixThreeSections(int** matrix, int row_start, int row_end, int col_start, int col_end, int target)
{
    int pivot_row;
    int search_idx;
    int pivot_col;
    
    //printf("%d,%d,%d,%d\n", row_start, row_end, col_start, col_end);
    pivot_row = (row_end - row_start + 1) / 2;
    pivot_col = (col_end - col_start + 1) / 2;
    //printf("[%d,%d]\n", pivot_row, pivot_col);
    if(matrix[row_start + pivot_row][col_start + pivot_col] == target) /* LOOP I */
        return true;
    else if(matrix[row_start + pivot_row][col_start + pivot_col] > target) /*LOOP I */
    {
        /* Search up for idx < target */
        
        while(pivot_row > 0 && matrix[row_start + pivot_row][col_start + pivot_col] > target)
            pivot_row--;
        if(matrix[row_start + pivot_row][col_start + pivot_col] > target) /* LOOP II */
        {
            /* Searched to Top, so recaculate the pivot_row */
            pivot_row = (row_end - row_start + 1) / 2;
            //printf("1.[%d,%d]\n", pivot_row, pivot_col);
            /* Search top left section */
            if(col_start + pivot_col - 1 >= col_start &&
                searchMatrixThreeSections(matrix, row_start, row_start + pivot_row, col_start, col_start + pivot_col - 1, target))
                return true;

            /* Search bottom left section */
            if(row_start + pivot_row + 1 <= row_end &&
                col_start + pivot_col + 1 <= col_end &&
                searchMatrixThreeSections(matrix, row_start, row_start + pivot_row + 1, col_start + pivot_col + 1, col_end, target))
                return true;
        }
        else if(matrix[row_start + pivot_row][col_start + pivot_col] == target) /* LOOP II */
            return true;
        else /* < target case */ /* LOOP II */
        {
            //printf("2. [%d,%d]\n", pivot_row, pivot_col);
            /* Bottom left section */
            if(row_start + pivot_row + 1 <= row_end &&
                col_start + pivot_col - 1 >= col_start &&
                searchMatrixThreeSections(matrix, row_start + pivot_row + 1, row_end, col_start, col_start + pivot_col - 1, target))
                return true;


            /* Top left section */
            if(col_start + pivot_col + 1 <= col_end &&
                searchMatrixThreeSections(matrix, row_start, row_start + pivot_row, col_start + pivot_col + 1, col_end, target))
                return true;
            
        }/* LOOP II end */
    }
    else /* < target case */ /* LOOP I */
    {
        /* Search down for idx > target */
        while((row_start + pivot_row) < row_end && matrix[row_start + pivot_row][col_start + pivot_col] < target)
            pivot_row++;
        //printf("3.1[%d,%d]\n", pivot_row, pivot_col);
        //printf("3.1:%d\n", matrix[row_start + pivot_row][col_start + pivot_col]);
        if(matrix[row_start + pivot_row][col_start + pivot_col] > target) /* LOOP II */
        {
            //printf("3.[%d,%d]\n", pivot_row, pivot_col);
            /* Bottom left section */
            if(col_start + pivot_col - 1 >= col_start &&
                searchMatrixThreeSections(matrix, row_start + pivot_row, row_end, col_start, col_start + pivot_col - 1, target))
                return true;

            /* Top left section */
            if(col_start + pivot_col + 1 <= col_end &&
               row_start + pivot_row - 1 >= row_start &&
                searchMatrixThreeSections(matrix, row_start, row_start + pivot_row - 1, col_start + pivot_col + 1, col_end, target))
                return true;
        }
        else if(matrix[row_start + pivot_row][col_start + pivot_col] == target) /* LOOP II */
            return true;
        else /* < target case */ /* LOOP II */
        {
            /* Searched to bottom, and still < target, so recalculate pivot_row */
            pivot_row = (row_end - row_start + 1) / 2;
            //printf("4.[%d,%d]\n", pivot_row, pivot_col);
            /* Search top right section */
            if(col_start + pivot_col + 1 <= col_end &&
                searchMatrixThreeSections(matrix, row_start, row_start + pivot_row, col_start + pivot_col + 1, col_end, target))
                return true;

            /* Search bottom right section */
            if(row_start + pivot_row + 1 <= row_end &&
                col_start + pivot_col + 1 <= col_end &&
                searchMatrixThreeSections(matrix, row_start + pivot_row + 1, row_end, col_start + pivot_col + 1, col_end, target))
                return true;
            
        }/* LOOP II end */
    } /* LOOP I end */
    return false;
}




bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target)
{
    return searchMatrixThreeSections(matrix, 0, matrixSize - 1, 0, *matrixColSize - 1, target);
}

/* 3-sections: 129 - 289ms(<27%) - 9.2MB, on Aug 31st, 2021 */
/* 2-secitons: 129 - 76ms(<51%) - 9.1MB, on Sep 1st, 2021 */
