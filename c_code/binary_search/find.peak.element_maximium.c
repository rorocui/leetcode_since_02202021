int find_peak_recursion(int* nums, int start, int end, int* idx)
{
    int mid;
    int i;
    int ret;
    int idx_top = -1, idx_bottom = -1;
    int ret_top, ret_bottom;


    if((end - start) < 3)
    {
        ret = nums[start];
        *idx = start;
        for(i = start + 1; i <= end; i++)
        {
            if(ret < nums[i]) 
            {
                ret = nums[i];
                *idx = i;
            }
        }
        return ret;
    }
    mid = start + (end - start) / 2;
    ret_top = find_peak_recursion(nums, start, mid, &idx_top); 
    ret_bottom = find_peak_recursion(nums, mid + 1, end, &idx_bottom);
    if(ret_top < ret_bottom)
    {
        ret = ret_bottom;
        *idx = idx_bottom;
    }
    else
    {
        ret = ret_top;
        *idx = idx_top;
    }

    return ret;

}

int findPeakElement(int* nums, int numsSize)
{
    int ret_idx;

    find_peak_recursion(nums, 0, numsSize - 1, &ret_idx);

    return ret_idx;

}

/* 63 - 3(<89%) - 5.9MB, on Jan 15th, 2022 */
