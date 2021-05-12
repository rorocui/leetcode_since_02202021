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

int heightChecker(int* heights, int heightsSize)
{
     int i, ret = 0;
         
     int* new_arr = malloc(sizeof(int) * heightsSize);
         
     for(i = 0; i < heightsSize; i++)
     {   
         new_arr[i] = heights[i];
     }   
         
     quicksort(new_arr, 0, heightsSize - 1); 
         
     for(i = 0; i < heightsSize; i++)
     {   
         //printf(",%d", new_arr[i]);
         //printf("%d-%d\n", heights[i], new_arr[i]);
         if(heights[i] != new_arr[i]) 
         {
             printf("*");
             ret++;
         }
     }
     //printf("\n");
         
     if(new_arr != NULL) free(new_arr);
     
     return ret;
    /* 81 cases in 4ms on Feb 28th, 2021 */
 
}

