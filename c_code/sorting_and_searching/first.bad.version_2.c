// The API isBadVersion is defined for you.
// bool isBadVersion(int version);


int firstBadVersion(int n) 
{
    int start, end, mid;

    start = 1;
    end = n;
    mid = start + (end - start) / 2;

    while(start < end)
    {
        if(isBadVersion(mid))
        {
            if(isBadVersion(mid - 1))
                end = mid - 1;
            else
                return mid;
        }
        else
        {
            if(isBadVersion(mid + 1))
                return mid + 1;
            else
                start = mid + 1;
        }
        mid = start + (end - start) / 2;
    }
    /* I don't think we could reach here for the search, but for the logic
     * I just return the start(start == end); */
    return start;
}
/* 22 - 0(<100%) - 5.6ms, on Jan 15th, 2022 */
