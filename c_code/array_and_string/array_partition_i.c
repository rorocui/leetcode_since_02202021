int min(int a, int b)
{
    if(a > b)
        return b;
    else
        return a;
}

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

int arrayPairSum(int* nums, int numsSize)
{
    int ret = 0;
    int i;
    quicksort(nums, 0, numsSize - 1);

    for(i = 0; i < numsSize; i++)
        printf("%d.", nums[i]);
    printf("\n");
    for(i = 0; i < numsSize; i += 2)
    {
       ret += nums[i]; 
    }
        
    return ret;

}

/* 83 - 60(<29%) - 7.7MB, on Aug 20th, 2021 */
