
int findMaxConsecutiveOnes(int* nums, int numsSize)
{
    int i;
    int max;
    int pre;
    int ret;
    
    ret = 0;
    max = 1;
    while(i < numsSize && nums[i] != 1) i++;
    if(i == numsSize) return 0;
    else pre = nums[i++];
    for(i; i < numsSize; i++) 
    {
        if(nums[i] == pre) 
            max++;
        else
        {
            while(i < numsSize && nums[i] != 1)
                i++;
            if(i < numsSize)
            {
                ret = ret < max ? max : ret;
                pre = nums[i];
                //printf("%d,%d\n", max, pre);
                max = 1;
            }
        }
    }   
    ret = ret < max ? max : ret;
    return ret;
}
/* 42 - 70(<8%) - 7.7MB, on Aug 21th, 2021 */
/* Dont count '0', 42 - 60(<12%) - 7.4MB, on Aug 21th, 2021 */
