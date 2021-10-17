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


void rotate(int** matrix, int matrixSize, int* matrixColSize)
{
    int i, j;
    int temp;


    temp = 0;
    /* diagomatrixSizeal switch */
    for(i = 0; i < matrixSize; i++)
        for(j = i + 1; j < matrixSize; j++)
        {
            temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }

    //print_matrix(matrix, matrixSize);
    /* vertical switch */
    for(i = 0; i < matrixSize; i++)
        for(j = 0; j < matrixSize / 2; j++)
        {
            temp = matrix[i][j];
            matrix[i][j] = matrix[i][matrixSize - j - 1];
            matrix[i][matrixSize - j - 1] = temp;
        }
    //print_matrix(matrix, matrixSize);
    
}
/* 21 - 4(<79%) - 6.4MB, on Oct 17th, 2021 */

