/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#define RETURN_ARR_SIZE 2

int compare(void const *a, void const *b)
{
    return *(int*)a - *(int*)b;
}



int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes){

    int** ret = NULL;
    int i;
    int min = INT_MAX;
    int temp = 0;



    ret = (int**)calloc(arrSize, sizeof(int*));
    ret[0] =(int*)malloc(sizeof(int) * RETURN_ARR_SIZE);
    *returnColumnSizes = (int*)malloc(sizeof(int) * arrSize);
    (*returnColumnSizes)[0] = RETURN_ARR_SIZE;
    *returnSize = 1;
    
    qsort(arr, arrSize, sizeof(int), compare);

    for(i = 1; i < arrSize; i++) {
        //printf("[%d]=%d\n", i, arr[i]);
        temp = abs(arr[i] - arr[i - 1]);
        if(temp < min)
        {
            min = temp;
            *returnSize = 1;
            ret[0][0] = arr[i - 1];
            ret[0][1] = arr[i];
            //printf("[%d]=%d,%d\n", i, arr[i - 1], arr[i]);
            
        }
        else if(temp == min)
        {
            *returnSize += 1; 
            if(ret[*returnSize - 1] == NULL)
                ret[*returnSize - 1] = (int*)malloc(sizeof(int) * RETURN_ARR_SIZE);
            ret[*returnSize - 1][0] = arr[i - 1];
            ret[*returnSize - 1][1] = arr[i];
            //printf("[%d]=%d,%d\n", i, arr[i - 1], arr[i]);
            (*returnColumnSizes)[*returnSize - 1] = RETURN_ARR_SIZE;
        }
    }
    /*
    printf("ret=%#x\n", ret);
    for(i = 0; i < *returnSize; i++){
        printf("ret[%d]=%#x\n", i, ret[i]);
        printf("[%d]=%d,%d\n", i, ret[i][0], ret[i][1]);
        //printf("columnsize=%d\n", returnColumnSizes[i][0]);
    }
    //printf("%d, %d, %d\n", ret[0][0], *returnSize, returnColumnSizes[0][0]);
    */
    
    return ret;
}


