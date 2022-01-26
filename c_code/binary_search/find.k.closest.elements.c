int locate_starter(int* arr, int arrSize, int k, int x, int mid)
{
    int counter = 1;
    int starter = mid;
    int end = mid + 1;

    while(counter <= k)
    {
        //printf("starter=%d, end=%d, counter=%d\n", starter, end, counter);
        if(starter < 0)
            return 0;
        else if(end > arrSize - 1)
        {
            if(counter++ < k)
                starter--;
        }
        else
        {
            if(abs(arr[starter] - x) <= abs(arr[end] - x))
            {
                //printf("inside-starter: starter=%d, end=%d, counter=%d\n", starter, end, counter);
                if(counter++ < k)
                    starter--;
            }
            else
            {
                //printf("inside-end: starter=%d, end=%d, counter=%d\n", starter, end, counter);
                end++;
                if(counter++ == k)
                    starter++;
                //printf("inside-a: starter=%d, end=%d, counter=%d\n", starter, end, counter);
            }
        }
    }
    return starter;
}

int* findClosestElements(int* arr, int arrSize, int k, int x, int* returnSize)
{
    int* ret = NULL;
    int start, end, mid;
    //printf("k=%d, x=%d\n", k, x);
    start = 0;
    end = arrSize - 1;
    mid = start + (end - start) / 2;

    *returnSize = k;
    ret = (int*)malloc(k * sizeof(int));

    if(x <= arr[0])
    {
        memcpy(ret, arr, (size_t)(k * sizeof(int)));
        return ret;
    }
    if(x >= arr[end])
    {
        memcpy(ret, &arr[arrSize - k], (size_t)(k * sizeof(int)));
        return ret;
    }

    while(start < end)
    {
        if(arr[mid] == x)
            break;
        if(arr[mid] < x)
            start = mid + 1;
        else
            end = mid - 1;
        mid = start + (end - start) / 2;
    }
    /* mid is already index of closest element to X */ 
    /* make sure mid is the closest element, which is smaller than x if possible. */
    if(mid > 0 && abs(arr[mid - 1] - x) <= abs(arr[mid] - x))
        mid--;
    

    //printf("mid=%d\n", mid);
    start = locate_starter(arr, arrSize, k, x, mid);
    memcpy(ret, &arr[start], (size_t)(k * sizeof(int)));
    
    return ret;
}
/* 63 - 80(<100%) - 15.4MB, on Jan 25th, 2022 */
