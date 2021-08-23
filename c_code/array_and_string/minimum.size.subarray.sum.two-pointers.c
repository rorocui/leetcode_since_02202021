int minSubArrayLen(int target, int* nums, int numsSize)
{
    int min_len = numsSize + 1;
    int pre, post;
    int sum;

    sum = pre = post = 0;
    while(post < numsSize)
    {
        sum += nums[post++];
        while(post < numsSize && sum < target)
            sum += nums[post++];
        if( sum >= target)
            min_len = min_len < (post - pre) ? min_len : (post - pre);
        while(pre <= post && sum >= target)
            sum -= nums[pre++];
        if(pre <= post) 
            min_len = min_len < (post - pre + 1) ? min_len : (post - pre + 1);
    }
    if(min_len == numsSize + 1)
        min_len = 0;

    return min_len;
}

/* 19 - 8(<81%) - 7.4MB, on Aug 22nd, 2021 */
