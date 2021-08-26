int removeDuplicates(int* nums, int numsSize)
{
    int pre;
    int i;
    int current;

    if(numsSize == 0) return 0;
    pre = 1;
    current = nums[0];
    for(i = 1; i < numsSize; i++)
    {
        if(nums[i] != current)
        {
            nums[pre++] = nums[i];
            current = nums[i];
        }
    }

    return pre;
}
/* 362 - 12 (<87%) - 7.7MB, on Aug 25th,2021 */
