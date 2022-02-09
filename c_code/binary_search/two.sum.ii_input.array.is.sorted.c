/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

/* return the idx of element to equal to the target */
/* Failure, return -1 */
int binary_search(int* nums, int start, int end, int target)
{
    int mid;

    while(start <= end)
    {
        mid = start + (end - start) / 2;
        //printf("s-%d, e-%d, m-%d, t-%d\n", start, end, mid, target);
        //printf("nums[%d]=%d\n", mid, nums[mid]);
        if(nums[mid] > target)
            end = mid - 1;
        else if(nums[mid] < target)
            start = mid + 1;
        else
            return mid;
    }
    return -1;
}

int* twoSum(int* numbers, int numbersSize, int target, int* returnSize)
{
    int i;
    int idx = 0;
    int* ret = NULL;

    *returnSize = 2;
    ret = (int*)calloc(*returnSize, sizeof(int));
    for(i = 0; i < numbersSize; i++)
    {
        //printf("[%d]:", i);
        if(target - numbers[i] >= numbers[i])
        {
            idx = binary_search(numbers, i + 1, numbersSize - 1, target - numbers[i]);
            //printf("search result=%d\n", idx);
            if(idx != -1)
            {
                ret[0] = i + 1;
                ret[1] = idx + 1;
                break;
            }
        }
        //printf("\n");
        /* else, we already cover the else case in former search, so we just skip this branch.
        */
    }

    return ret;

}
/* 21 - 12ms(<49%) - 7.4MB, on Feb 2022 */
