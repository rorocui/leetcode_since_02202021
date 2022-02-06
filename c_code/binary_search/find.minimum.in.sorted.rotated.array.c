int findMin(int* nums, int numsSize)
{
    int start, end, mid;

    start = mid = 0;
    end = numsSize - 1;

    while(start < end)
    {
        mid = start + (end - start) / 2;
        if(nums[mid] > nums[end])
            start = mid + 1;
        else if(nums[mid] < nums[end])
            end = mid;
        else
            end--;
    }
    return nums[start];

}
/* 193 - 3(<91%) - 5.9MB, on Feb 6th, 2022 */
