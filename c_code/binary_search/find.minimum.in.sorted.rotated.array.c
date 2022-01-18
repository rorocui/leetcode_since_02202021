int findMin(int* nums, int numsSize)
{
    int start, end, mid, pre_mid;

    start = 0;
    end = numsSize - 1;
    pre_mid = mid = 0;
    
    /* for non rotated array */
    if(nums[start] < nums[end])
        return nums[start];
    while(start < end)
    {
        if(nums[mid] > nums[mid + 1])
            return nums[mid + 1];
        else
        {
            if(nums[pre_mid] < nums[mid + 1])
            {
                pre_mid = mid;
                start = mid + 1;
            }
            else
                end = mid;
            mid = start + (end - start) / 2;
        }
    }
    return nums[start];
}
/* 150 - 0(<100%) - 6MB, on Jan 17th, 2022 */
