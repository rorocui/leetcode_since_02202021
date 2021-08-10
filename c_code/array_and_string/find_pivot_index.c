

int pivotIndex(int* nums, int numsSize)
{
    int i; 
    int left_sum = 0;
    int total_sum = 0;
    
    for(i = 0; i < numsSize; i++)
    {
       total_sum += nums[i]; 
    }
    for(i = 0; i < numsSize; i++)
    {
        total_sum -= nums[i];
        if(total_sum == left_sum) return i;
        left_sum += nums[i];
    }
    
    return -1;

}

/* 742 - 20ms(<56%) - 6.6MB, on Aug 9th, 2021 */
