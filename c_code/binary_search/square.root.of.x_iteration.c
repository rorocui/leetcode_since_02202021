int mySqrt(int x)
{
    int start, end, mid;
    
    if(x <= 0) return 0;
    start = 1;
    end = x;
    mid = start + (end - start) / 2;
    while(start < end)
    {
       if(end == start + 1) return start;
       if(mid == x / mid)
            return mid;
        else if(mid < x / mid) 
            start = mid;
        else
            end = mid;
        mid = start + (end - start) / 2;
    } 
    return start;
    
}
/* 1017 - 0(<100%) -5.8MB, on Jan 9th, 2022 */
