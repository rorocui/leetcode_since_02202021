#define LEN 9

int* check_num_set(char** board, int row, int col)
{
    int* new = NULL;
    int i, j;
    //int debug = 9;

    //if(row == debug) printf("check_num_set:%#x[%d][%d]\n", board, row, col);
    new = (int*)calloc(LEN, sizeof(int));
    for(j = 0; j < LEN; j++)
    {
        if(board[row][j] != '.')
        {
            //if(row == debug) printf("[%d][%d]=%c\n", row, j, board[row][j]);
            new[board[row][j] - 0x31] = 1; 
        }
    }
    for(i = 0; i < LEN; i++)
    {
        if(board[i][col] != '.')
        {
            //if(row == debug) printf("[%d][%d]=%c\n", i, col, board[i][col]);
            new[board[i][col] - 0x31] = 1; 
        }
    }
    for(i = (row / 3) * 3; i < (row / 3 + 1) * 3; i++)
    {
        for(j = (col / 3) * 3; j < (col/ 3 + 1) * 3; j++)
        {
            //if(row == debug) printf("board[%d][%d]<[%d]\n", i, j, (row / 3 + 1) * 3);
            if(board[i][j] != '.')
            {
                //if(row == debug) printf("board[%d][%d]=%c\n", i, j, board[i][j]);
                new[board[i][j] - 0x31] = 1;
            }
        }
    }

    /*
    for(i = 0; i < LEN; i++)
        printf("%d.", new[i]);
    printf("\n");
    */
    return new;

}

bool is_array_empty(int* new)
{
    int i;
    bool ret = true;
    
    for(i = 0; i < LEN; i++)
    {
        if(new[i] == 0)
        {
            //printf("%d.",i + 1);
            ret = false;
        }
    }
    //printf("\n");
    
    return ret;
}

void print_array(int* new)
{
    for(int i = 0; i < LEN; i++)
        if(new[i] == 0)
        {
            printf("%d.",i + 1);
        }
    printf("\n");
}

void print_matrix(char** matrix, int size)
{
    int i, j;
    for(i = 0; i < size; i++)
    {
        printf("[");
        for(j = 0; j < size; j++)
            printf("%c ", matrix[i][j]);
        printf("]\n");
    }
    printf("\n");
}

bool search_next_dot(char** board, int start_row, int start_col, int* find_row, int* find_col)
{
    *find_row = start_row;
    *find_col = start_col;
    while(true)
    {
        //printf("[%d][%d]-%c\n", *find_row, *find_col, board[*find_row][*find_col]);
        if(board[*find_row][*find_col] == '.')
        {
            return true;
        }
        (*find_col)++;
        if(*find_col == LEN)
        {
            *find_col = 0;
            (*find_row)++;
        }
        if(*find_row == LEN)
        {
            return false;
        }
    }
}

bool backtrack_sudoku(char** board, int row, int col)
{
    int* candidate = NULL;
    int idx, i, j;
    int debug = 9;

    /*
    if(row == debug) 
    {
        printf("%#x[%d][%d]\n", board, row, col);
        print_matrix(board, 9); 
    }
    */
    candidate = check_num_set(board, row, col);
    if(is_array_empty(candidate)) 
    {
        free(candidate);
        return false;
    }
    /*
    if(row == debug) 
        print_array(candidate);
    */
    for(idx = 0; idx < LEN; idx++)
    {
        if(candidate[idx] == 0)
        {
            board[row][col] = (char)(idx + 0x31);
            if(search_next_dot(board, row, col, &i, &j))
            {
                    if(backtrack_sudoku(board, i, j)) 
	                {
                        //if(row == debug) print_matrix(board, 9); 
	                    free(candidate);
	                    return true;
	                }
                    else
                    {
                        //backtrack and break;
                        //if(row == debug) printf("backtrack[%d][%d]=%c\n", row, col, board[row][col]);
                        board[row][col] = '.';
                    }
            }
            else
            {
	            free(candidate);
                return true;
            }
        } /* if candidate == 0 */
    }/* for */
    free(candidate);
    return false;
}

void solveSudoku(char** board, int boardSize, int* boardColSize)
{
    int i, j;

    i = j = 0;
    if(search_next_dot(board, 0, 0, &i, &j))
        if(backtrack_sudoku(board, i, j))
            printf("true\n");
        else
            printf("false\n");
                
    //print_matrix(board, 9); 
}
/* 6 - 37(<5%) - 9.9MB, on Sep 18th, 2021 */
