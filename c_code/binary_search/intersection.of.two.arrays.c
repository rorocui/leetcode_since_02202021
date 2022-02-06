/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int compare(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

bool binary_search(int* nums, int nums_len, int target)
{
    int start, end, mid;

    start = mid = 0;
    end = nums_len - 1;
    while(start <= end)
    {
        mid = start + (end - start) / 2;
        if(nums[mid] > target)
            end = mid - 1;
        else if(nums[mid] < target)
            start = mid + 1;
        else
        {
            //printf("found %d.\n", target);
            return true;
        }
    }
    //printf("Can't found %d.\n", target);
    return false;
}

int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize)
{
    int *search_base = NULL,
        *target_set = NULL;
    int i, target_array_len, search_len, idx = 0;
    int target = -1;
    int* ret = NULL;


    /*
     m >> n(m = 1000, n=2)
      1. (n + 1)logm + logn = 3x9.9 + 2 = 32
      2. logm + (m + 1)logn = 9.9 + 1000 x 2 = 2010  
      log1000 base2 = 9.9
     */
    if(nums1Size > nums2Size)
    {
        search_base = nums1;
        target_set = nums2;
        target_array_len = nums2Size;
        search_len = nums1Size;
    }
    else
    {
        search_base = nums2;
        target_set = nums1;
        target_array_len = nums1Size;
        search_len = nums2Size;
    }
    ret = (int*)calloc(target_array_len, sizeof(int));

    qsort(nums1, nums1Size, sizeof(int), compare);
    qsort(nums2, nums2Size, sizeof(int), compare);
    for(i = 0; i < target_array_len; i++)
    {
        //printf("targetset[%d]=%d\n", i, target_set[i]);
        if(target == target_set[i])
            continue;
        else
            target = target_set[i];
        if(binary_search(search_base, search_len, target))
                ret[idx++] = target;
    }
    *returnSize = idx;

    return ret;
}
/* Time complexity
* nums1Size > nums2Size, then O(nums2Size(log nums1Size))
*/
/* 55 - 5(<65%) - 6.1MB, on Feb 6th, 2022 */
