int search_pivot_index(int* nums, int numsSize)
{
    int start, end, mid;

    start = 0;
    end = numsSize - 1;
    mid = start + (end - start) / 2;
    if(mid == start) mid++;

    if(nums[start] < nums[end]) return 0;
    while(start < end)
    {
        //printf("%s:s-%d,m-%d,e-%d\n", __func__, start, mid, end);
        if(nums[start] < nums[mid])
        {
            if(nums[mid] > nums[mid + 1])
                return mid + 1;
            else
                start = mid + 1;
        }
        else
        {
            //printf("%d,%d\n", nums[start], nums[mid - 1]);
            if(nums[start] > nums[mid - 1])
                end = mid - 1;
            else
                return mid;
        }
        mid = start + (end - start) / 2;
        if(mid == start) mid++;
    }
    /*looks like that is not rotated array at all. */
    return 0;
}

int index_pivot(int idx, int pivot_idx, int size)
{
    return (idx + pivot_idx) % size;
}

int search(int* nums, int numsSize, int target)
{
    int start, end, mid;
    int pivot_idx = 0;

    start = 0;
    end = numsSize - 1;
    mid = start + (end - start) / 2;
    pivot_idx = search_pivot_index(nums, numsSize);
    //printf("%d\n", pivot_idx);
    while(start <= end)
    {
        //printf("s-%d,e-%d\n", start, end);
        //printf("mid=%d, idx=%d, nums=%d\n", mid, index_pivot(mid, pivot_idx, numsSize), nums[index_pivot(mid, pivot_idx, numsSize)]);
        if(nums[index_pivot(mid, pivot_idx, numsSize)] == target)
            return index_pivot(mid, pivot_idx, numsSize);
        if(nums[index_pivot(mid, pivot_idx, numsSize)] < target)
            start = mid + 1;
        else
            end = mid - 1;
        mid = start + (end - start) / 2;
    }
    /* failed to search the target, return -1; */
    return -1;

}
/* 192 - 2ms(<75%) - 6MB, On Jan 13th, 2022 */
