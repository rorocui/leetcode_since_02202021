

int search(int* nums, int numsSize, int target)
{
    //printf("%d[%d]\n", nums[0], numsSize);
    int half = numsSize / 2;
    int ret = 0;
    
    if(numsSize <= 0)
        return -1;
    
    if(target == nums[half])
        return half;
    else if(target < nums[half])
        return search(nums, half, target);
    else
    {
        ret = search(&nums[half + 1], (numsSize - half - 1), target);
        if(ret == -1)
            return ret;
        else
            return ret + half + 1;
    }

}
/* 47 - 28(<98%) - 7.3MB, on Dec 19th, 2021 */
