void swap(int* a, int* b)
{
    //printf("%d-%d\n", *a, *b);
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int* nums, int low, int high)
{
    /*printf("%#x, %d-%d\n", nums, low, high);
    for(int j = low; j <= high; j++)
        printf("%d ", nums[j]);
    printf("\n");
    */
    int i, idx, pivot;

    idx = low - 1;
    pivot = nums[high];
    for(i = low; i <= high - 1; i++)
    {
        //printf("nums[%d]-%d vs pivot-%d\n", i, nums[i], pivot);
        if(nums[i] < pivot)
        {
            idx++;
            //printf("idx-%d, i-%d\n", idx, i);
            swap(nums + idx, nums + i);
        }
    }
    //printf("idx-%d, high-%d\n", idx, high);
    swap(nums + idx + 1, nums + high);

    /*
    for(int j = low; j <= high; j++)
        printf("%d ", nums[j]);
    printf("\nreturn %d\n", idx + 1);
    */
    return idx + 1;
}

int partition_r(int* nums, int low, int high)
{
    int idx = low;
    
    srand(time(NULL));
    idx += rand() % (high - low);
    swap(nums + idx, nums + high);
    
    return partition(nums, low, high);
    
}


void sort_array_recursion(int* nums, int low, int high)
{
    /*
    printf("%s:", __func__);
    for(int j = low; j <= high; j++)
        printf("%d ", nums[j]);
    printf("\n");
    */
    if(low < high)
    {
        int pivot = partition_r(nums, low, high);

        sort_array_recursion(nums, low, pivot - 1);
        sort_array_recursion(nums, pivot + 1, high);
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArray(int* nums, int numsSize, int* returnSize)
{
    *returnSize = numsSize;
    sort_array_recursion(nums, 0, numsSize - 1);

    return nums;
}

/* 276(<35%) - 25.6MB, on March 7th, 2022 */
