// The API isBadVersion is defined for you.
// bool isBadVersion(int version);
int firstBadVersion(int n) 
{
    int bad;
    long min, max;

    bad = n / 2;
    min = 0;
    max = n;
    while(bad != n || bad != 1)
    {
        //printf("bad=%d,%d\n", bad, isBadVersion(bad));
        if(isBadVersion(bad))
        {
            if(isBadVersion(bad - 1))
            {
                max = bad;
                bad = (int)((min + max) / 2);
            }
            else
                return bad;
        }
        else
        {
            if(isBadVersion(bad + 1))
                return bad + 1;
            else
            {
                min = bad;
                bad = (int)((min + max) / 2);
            }
        }
    }
    return bad;

}
/* 22 - 3(<18%) - 5.5MB, on Oct 14th, 2021 */
/* 22 - 0(<100%) - 5.6MB, on Jan 15th, 2022 */

