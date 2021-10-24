int maxSubArray(int* nums, int numsSize)
{
    int max_sum,
        i,
        sub_sum = 0;

    if(numsSize <= 0) return 0;

    max_sum = nums[0];
    for(i = 0; i < numsSize; i++)
    {
        sub_sum += nums[i];
        if(sub_sum > max_sum)
            max_sum = sub_sum;
        if(sub_sum < 0)
            sub_sum = 0;
    }

    return max_sum;

}
/* 209 - 174(<15%) - 12.5MB, on Oct 24th, 2021 */ 
