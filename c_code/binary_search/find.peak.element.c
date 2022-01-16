int findPeakElement(int* nums, int numsSize)
{
    int start, end, mid;

    start = 0;
    end = numsSize - 1;
    mid = start + (end - start) / 2;
    while(start < end)
    {
        if(start == mid) return nums[mid] > nums[end] ? mid : end;
        if(nums[mid] < nums[mid + 1])
        {
            start = mid + 1;
        }
        else if(nums[mid - 1] > nums[mid])
        {
            end = mid - 1;
        }
        /* mush be this condition (nums[mid - 1] < nums[mid] && nums[mid] > nums[mid + 1]) */
        else
            return mid;
        mid = start + (end - start) / 2;
    }
    /* should not reach here to be complete, add return failure here. */
    return start; 
}
/* 63 - 0(<100%) - 5.7MB, on Jan 15th, 2022 */
