/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#define RETURN_ARR_SIZE 2

void swap(int** a, int** b){
    int* temp = *a;
    *a = *b;
    *b = temp;
}


int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes){

    int** ret = NULL;
    int i, j;
    int min = INT_MAX;
    int temp = 0;
    int idx;
    bool bubble_swap = true;



    ret = (int**)calloc(arrSize, sizeof(int*));
    ret[0] =(int*)malloc(sizeof(int) * RETURN_ARR_SIZE);
    *returnColumnSizes = (int*)malloc(sizeof(int) * arrSize);
    (*returnColumnSizes)[0] = RETURN_ARR_SIZE;
    *returnSize = 1;
    

    for(i = 0; i < arrSize; i++) {
        for(j = i + 1; j < arrSize; j++) { 
	        temp = abs(arr[i] - arr[j]);
	        if(temp < min)
	        {
	            min = temp;
	            *returnSize = 1;
                /* no sorting for output array, will do that out of this double for loop */
                if(arr[i] > arr[j]){
	                ret[0][0] = arr[j];
	                ret[0][1] = arr[i];
                }
                else{
	                ret[0][0] = arr[i];
	                ret[0][1] = arr[j];
                }
	            
	        }
	        else if(temp == min)
	        {
	            *returnSize += 1; 
                idx = *returnSize - 1;
	            if(ret[idx] == NULL)
	                ret[idx] = (int*)malloc(sizeof(int) * RETURN_ARR_SIZE);
                if(arr[i] > arr[j]){
	                ret[idx][0] = arr[j];
	                ret[idx][1] = arr[i];
                }
                else {
	                ret[idx][0] = arr[i];
	                ret[idx][1] = arr[j];
                }

	            (*returnColumnSizes)[idx] = RETURN_ARR_SIZE;
	        }
        }
    }/* end of for i*/
    /*Bubble sort the output array, and compare the first item of each pair, and then swap the address only */
    while(bubble_swap) {
        bubble_swap = false;
        for(i = 0; i < *returnSize - 1; i++){
            if(ret[i][0] > ret[i + 1][0]) {
                swap(&ret[i], &ret[i + 1]);
                bubble_swap = true;
            }
        }
    }
    return ret;
}


