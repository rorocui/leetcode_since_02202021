void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sortColors(int* nums, int numsSize){
    int idx1 = 0;

    for(int i = 0; i < numsSize - 1; i++){
        idx1 = i;
        for(int j = i + 1; j < numsSize; j++){
            if(nums[idx1] > nums[j])
                idx1 = j;
        }
        //printf("i=%d,idx1=%d\n", i, idx1);
        if(i != idx1) swap(&nums[i], &nums[idx1]);
    }
}
/* beats 53% on Sep 1st, 2022 */
