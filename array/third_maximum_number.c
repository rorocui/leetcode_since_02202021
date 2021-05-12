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

int thirdMax(int* nums, int numsSize)
{
    int i, max1, max2, max3;
    bool find_max2 = false, find_max3 = false;

    if(numsSize == 0) return 0;
    max1 = nums[0];

    //printf("%d,%d\n", max1, numsSize);
    for(i = 1; i < numsSize; i++)
    {
        //printf("for:%d,%d,%d\n", max1, max2, max3);
        if( find_max2 )
        {
            if( find_max3)
            {
                if(nums[i] > max3 && nums[i] < max2)
                    max3 = nums[i];
                else if(nums[i] > max2 && nums[i] < max1)
                {
                    max3 = max2;
                    max2 = nums[i];
                }
                else if(nums[i] > max1)
                {
                    max3 = max2;
                    max2 = max1;
                    max1 = nums[i];
                }
            }
            else
            {
                if(nums[i] < max2)
                {
                    max3 = nums[i];
                    find_max3 = true;
                }
                else if(nums[i] > max2 && nums[i] < max1)
                {
                    max3 = max2;
                    max2 = nums[i];
                    find_max3 = true;
                }
                else if(nums[i] > max1)
                {
                    max3 = max2;
                    max2 = max1;
                    max1 = nums[i];
                    find_max3 = true;
                }
            }
        }
        else
        {
            if(nums[i] < max1)
            {
                max2 = nums[i];
                find_max2 = true;
            }
            else if(nums[i] > max1)
            {
                max2 = max1;
                max1 = nums[i];
                find_max2 = true;
            }
        }
    }
    //printf("%d,%d,%d,%d\n", max1, max2, max3, find_max3);
    if(find_max3)
        return max3;
    else
        return max1;
    /* 27 cases in 4 ms, beats 94.27% on March 1st, 2021 */
}
