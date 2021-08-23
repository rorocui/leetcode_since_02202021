int findMaxConsecutiveOnes(int* nums, int numsSize){
    int max = 0, counter = 0;
    for(int i =0; i < numsSize; i++)
    {
        if(nums[i] == 1) 
            counter++;
        else
        {
            if(counter > max) max = counter;
            counter = 0;
        }
    }
    if(counter > max) max = counter;
    return max;
}
/* 42 - 44(<20%) - 7.5MB , on Aug 21th, 2021 */
