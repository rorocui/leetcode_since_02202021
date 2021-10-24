int rob(int* nums, int numsSize) {
    int pre = 0, cur = 0;
    for (int i = 0; i < numsSize; ++i) {
        //printf("[%d]%d+%d\n", i, nums[i],  pre);
        int tmp = nums[i] + pre;
        pre = cur;
        cur = (tmp > pre ? tmp : pre);
    }
    return cur;
}
/* 68 - 0(<100%) - 6.1MB, on Oct 24th, 2021 */
