/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int compare(const void* a, const void * b)
{
    return *(int*)a - *(int*)b;
}

bool binary_search(int* nums, int len, int target)
{
    int start, end, mid;
    
    start = mid = 0;
    end = len - 1;
    while(start <= end)
    {
        mid = start + (end - start) / 2;
        //printf("s-%d, e-%d, m-%d\n", start, end, mid);
        if(nums[mid] > target)
            end = mid - 1;
        else if(nums[mid] < target)
            start = mid + 1;
        else
        {
            if(mid + 1 < len)
            {
                //printf("memcpy mid=%d, len=%d\n", mid, (len - mid - 2) * sizeof(int));
                //printf("%#x,%#x, %#x-%d\n", &nums[mid], &nums[mid + 1], &nums[4], nums[4]);
                //memcpy(&(nums[mid]), &(nums[mid + 1]), sizeof(int) * (len - mid - 2));
                memmove(&(nums[mid]), &(nums[mid + 1]), sizeof(int) * (len - mid - 1));
            }    
            return true;
        }
    }
    return false;
}

void print_array(int* nums, int len)
{
    printf("%#x:", nums);
    for(int i = 0; i < len; i++)
        printf("%d ", nums[i]);
    printf("\n");
}

int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize)
{
    int *ret = NULL,
        *search_base = NULL,
        *target_set = NULL;
    int i, idx = 0;
    int target_len, search_len;

    if(nums1Size > nums2Size)
    {
        search_base = nums1;
        target_set = nums2;
        search_len = nums1Size;
        target_len = nums2Size;
    }
    else
    {
        search_base = nums2;
        target_set = nums1;
        search_len = nums2Size;
        target_len = nums1Size;
    }
    ret = (int*)calloc(target_len, sizeof(int));

    qsort(nums1, nums1Size, sizeof(int), compare);
    qsort(nums2, nums2Size, sizeof(int), compare);
    for(i = 0; i < target_len; i++)
    {
        //print_array(search_base, search_len);
        if(binary_search(search_base, search_len - idx, target_set[i]))
        {
            //qsort(search_base, search_len, sizeof(int), compare);
            ret[idx++] = target_set[i];
        }
        //print_array(search_base, search_len);
    }
    *returnSize = idx;

    return ret;
}

/* 56 - 8(<49%) - 6.5MB, on Feb 7th, 2022 */
