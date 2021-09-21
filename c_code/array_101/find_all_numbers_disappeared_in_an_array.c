/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize)
{
    int i;

    *returnSize = 0;
    int* new_nums = NULL;

    new_nums = (int*)calloc(numsSize, sizeof(int));

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
}
/*34 cases in 96ms, beats 92.02% on March 1st, 2021 */
/* 33 - 145(<24%) - 18MB, on Sep 19th,2021 */
