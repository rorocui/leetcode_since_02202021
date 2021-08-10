int dominantIndex(int* nums, int numsSize)
{
    int i;
    int max, less_max;
    int idx = 0;
    
    
    if(numsSize == 1) return 0;
    max = less_max = 0;
    for(i = 0; i < numsSize; i++)
    {
        if(nums[i] > max)
        {
            less_max = max;
            max = nums[i];
            idx = i;
        }
        else if(nums[i] > less_max)
            less_max = nums[i];
    }
    //printf("%d,%d\n", max, less_max);
    
    if(max >= less_max * 2) return idx;
    else return -1;
}

/* 232 - 0ms(n/a) - 6MB, on Aug 9th, 2021 */
