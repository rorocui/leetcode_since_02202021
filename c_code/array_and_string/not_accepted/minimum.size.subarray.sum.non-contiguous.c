void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* nums, int low, int high)
{
    int i;
    int idx = low;
    int pivot = nums[high];

    for(i = low; i < high; i++)
    {
        if(nums[i] < pivot)
            swap(&nums[idx++], &nums[i]);
    }
    nums[high] = nums[idx];
    nums[idx] = pivot;

    return idx;
}

void quicksort(int* nums, int low, int high)
{
    //printf("quicksort-%d,%d\n", low, high);
    int idx;
    idx = partition(nums, low, high);

    if(low < (idx - 1)) quicksort(nums, low, idx - 1);
    if((idx + 1) < high) quicksort(nums, idx + 1, high);
}


int minSubArrayLen(int target, int* nums, int numsSize)
{
    int i = numsSize - 1;
    int ret = 0;

    quicksort(nums, 0, numsSize - 1);
    for(int j = 0; j < numsSize; j++)
        printf("%d.", nums[j]);
    printf("\n");
    while( i >= 0 && (ret += nums[i]) < target)
    {
        printf("[%d]ret=%d\n", i, ret);
        i--;
    }
    if(i < 0) return 0;
    else return (numsSize - i);

}

