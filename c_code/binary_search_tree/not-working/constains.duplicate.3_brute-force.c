bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int k, int t){
    long min = INT64_MAX;
    long temp = 0;
    int i,j;

    printf("size=%d\n", numsSize);
    for(i = 0; i < numsSize; i++)
    {
        for(j = i + 1; j <= (i + k) && j < numsSize; j++)
        {
                temp = labs((long)nums[i] - nums[j]);
                min = (min > temp) ? temp : min;
                //printf("%d,%d -- #%x?#%x\n", i, j, min, temp);
                if(min <= t) return true;
        }
    }

    return false;
}

