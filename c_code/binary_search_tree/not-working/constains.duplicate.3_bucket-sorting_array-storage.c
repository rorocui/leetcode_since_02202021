
/* Since story the bucket sorting result in array will cause memory limit exceeded
 * Will use bit operation to store the bucket sorting, the as INT_MAX * 2 range
 * That requires (INT_MAX * 2) / 64 long long to store the whole bucket sorting result */

void set_bucket(long* bucket, long index)
{
    bucket[index/64] |= (1 << (index % 64));
}

void clean_bucket(long* bucket, long index)
{
    bucket[index/64] &= ~(1 << (index % 64));
}

bool check_bucket(long* bucket, long index)
{
    return bucket[index/64] ^ (1 << (index % 64));
}

bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int k, int t)
{
    long* bucket = calloc(I

}
