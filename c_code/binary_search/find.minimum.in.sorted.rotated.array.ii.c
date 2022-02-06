int findMin(int* nums, int numsSize)
{
    int start, end, mid, pre_mid;


    pre_mid = start = 0; 
    end = numsSize - 1;
    mid = start + (end - start) / 2;

    if(nums[start] < nums[end)
        return nums[start];

    while(start < end)
    {
        /* mid = start + (end - start) / 2;
         * mid  == end;
         * end = start / 2 + end / 2;
         * end / 2  = start / 2
         * end = start 
         * */
        if(nums[pre_mid] <= nums[mid])
        {
            pre_mid = mid;
            start = mid;
        }
        else
        {
            end = mid;
        }
    }
    return nums[start];
}
