void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;    
}

int partition(int* arr, int low, int high)
{
    int temp, pivot = arr[high];
    int i = low -1;
    
    for(int j = low; j <= high - 1; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quicksort(int* arr, int low, int high)
{
    int pivot = 0;
    
    if(low < high)
    {
        pivot = partition(arr, low, high);
        quicksort(arr, low, pivot - 1);
        quicksort(arr, pivot + 1, high);
    }
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize)
{
    int i;

    *returnSize = 0;
    int* new_nums = malloc(sizeof(int) * numsSize);

    for(i = 0; i < numsSize; i++)
        new_nums[i] = 0;

    for(i = 0; i < numsSize; i++)
        new_nums[nums[i] - 1] = 1;

    for(i = 0; i < numsSize; i++)
    {
        if(new_nums[i] == 0)
        {
            new_nums[*returnSize] = i + 1;
            (*returnSize)++;
        }
    }
    return new_nums;
    /*34 cases in 96ms, beats 92.02% on March 1st, 2021 */
}
