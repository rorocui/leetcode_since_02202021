void sortColors(int* nums, int numsSize){
    int num_total = 0;
    int num_ones = 0;
    int num_twos = 0;
    int i;

    for(i = 0; i < numsSize; i++){
        if(nums[i] == 1)
            num_ones++;
        num_total += nums[i];
    }
    num_twos = (num_total - num_ones) / 2;

    for(i = 0; i < (numsSize - num_ones - num_twos); i++){
        nums[i] = 0;
    }
    for(i = numsSize - num_ones - num_twos; i < (numsSize - num_twos); i++){
        nums[i] = 1;
    }
    for(i = numsSize - num_twos; i < numsSize; i++){
        nums[i] = 2;
    }
}
/* beats 100% on Sep 6th, 2022 */
