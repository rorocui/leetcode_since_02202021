
static int count;

void swap(int* a, int* b){
    //printf("%p,%p,%d-%d\n", a, b, *a, *b);
    count++;
    int temp = *a;
    *a = *b;
    *b = temp;
    //printf("%p,%p,%d-%d\n", a, b, *a, *b);
}

void print_array(int* nums, int size){
    for(int i = 0; i < size; i++)
        printf("%d,", nums[i]);
    printf("\n");
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArray(int* nums, int numsSize, int* returnSize){
    int idx_end;
    int i;
    int temp;
    

    count = 0;
    temp = 0;
    idx_end = numsSize - 1;
    while(idx_end > 0){
	    for(i = idx_end; i >= 0; i--){
#ifdef SWAP_SAVING                
	        if((2*i + 2) <= idx_end) { 
                if (nums[2*i + 2] > nums[2*i + 1]) {
                    if(nums[2*i + 2] > nums[i]){
	                    //swap(&nums[i] , &nums[2*i + 2]);
                        temp = nums[i];
                        nums[i] = nums[2*i+2];
                        nums[2*i+2] = temp;
                        //print_array(nums, numsSize);
                        //i = 2*i + 2 + 1;
                    }
                } else {
                    if(nums[2*i + 1] > nums[i]){
	                    //swap(&nums[i] , &nums[2*i + 1]);
                        temp = nums[i];
                        nums[i] = nums[2*i+1];
                        nums[2*i+1] = temp;
                        //print_array(nums, numsSize);
                        //i = 2*i + 1 + 1;
                    }
                }
            } else if((2*i + 1) <= idx_end) {
                if(nums[2*i + 1] > nums[i]) {
	                //swap(&nums[i] , &nums[2*i + 1]);
                        temp = nums[i];
                        nums[i] = nums[2*i+1];
                        nums[2*i+1] = temp;
                    //print_array(nums, numsSize);
                    i = 2 * i + 1 + 1;
                }
            }
#else
            if((2*i + 1) <= idx_end && nums[i] < nums[2*i + 1]) {
                swap(&nums[i] , &nums[2*i + 1]);
                //print_array(nums, numsSize);
            }
            if((2*i + 2) <= idx_end && nums[i] < nums[2*i + 2]) {
                swap(&nums[i] , &nums[2*i + 2]);
                //print_array(nums, numsSize);
            }
#endif               
	    } // end of for
        //printf("before final swap %d\n", idx_end);
        swap(&nums[0], &nums[idx_end]);
        //print_array(nums, numsSize);
        idx_end--;
        //printf("%d\n", idx_end);
    } // end of while

    *returnSize = numsSize;
    printf("swap count is %d\n", count);

    return nums;
}

