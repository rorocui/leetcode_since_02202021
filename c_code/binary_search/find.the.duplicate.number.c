
int cmp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int findDuplicate(int* nums, int numsSize)
{
    int start, end, mid;
    
    start = mid = 0;
    end = numsSize - 1;

    qsort(nums, numsSize, sizeof(int), cmp);
    while(start < end)
    {
        mid = start + (end - start) / 2;
        if(nums[mid] == mid)
        {
            if(nums[mid - 1] == mid - 1)
                end = mid - 1;
            else
                return mid;
        }
        else if(nums[mid] < mid)
            end = mid - 1;
        else
            start = mid + 1;
    }
    /* I don't think that is good case to reach here */
    return nums[start];
}


/* 58 - 140(<54%) - 14.3MB,  On Feb 10th, 2022 */
