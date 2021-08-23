void rotate(int* nums, int numsSize, int k)
{
    int* temp = NULL;
    int i;

    k = k % numsSize;
    temp = (int*)calloc(numsSize - k, sizeof(int));
    for(i = 0; i < (numsSize - k); i++)
        temp[i] = nums[i];
    for(i = 0; i < k; i++)
        nums[i] = nums[i + numsSize - k];
    for(i = k; i < numsSize; i++)
        nums[i] = temp[i - k];

    free(temp);
}

/* 37 - 108ms(<65%) - 22.5MB, on Aug 22nd, 2021 */
/* no if (numsSize == 1) 37 - 100ms(<94%) - 22.6MB, on Aug 22nd, 2021 */
