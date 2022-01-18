/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize)
{
    int* ret = NULL;
    int start, end, mid;
    int idx_left = 1,
        idx_right = 1;

    *returnSize = 2;
    start = 0;
    end = numsSize - 1;
    mid = start + (end - start) / 2;
    ret = (int*)malloc(2 * sizeof(int));
    ret[0] = ret[1] = -1;

    if(numsSize == 0)
        return ret;
    if(numsSize == 1)
    {
        if(nums[0] == target)
            ret[0] = ret[1] = 0;
        return ret;
    } 

    while(start + 1 <= end)
    {
        //printf("%d,mid=%d,%d\n", start, mid, end);
        if(nums[mid] == target)
        {
            idx_right = idx_left = 1;
            while((mid + (idx_right)) <= end && nums[mid + (idx_right)] == target)
                idx_right++;
            //printf("idx_right=%d\n", idx_right);
            while((mid - (idx_left)) >= start && nums[mid - (idx_left)] == target)
                idx_left++;
            ret[0] = mid - idx_left + 1;
            ret[1] = mid + idx_right - 1;

            return ret;
        }
        else if(nums[mid] < target)
            start = mid + 1;
        else
            end = mid - 1;
        mid = start + (end - start) / 2;
    }
    if(start == end && nums[start] == target)
        ret[0] = ret[1] = start;
    return ret;
}
/* 88 - 4(< 99.5%) - 7.7MB, on Jan 17th, 2022 */
