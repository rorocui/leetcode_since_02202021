int mySqrt_recursion(int x, int start, int end)
{
    //printf("%d,%d,%d\n", x, start, end);
    if(end == start + 1) return start;
    int mid = start + (end - start ) / 2;
    if(mid == 0) return mid;
    int mid_compare = mid - (x / mid);

    //if(-1 < mid_compare && mid_compare < 1)
    if(mid_compare == 0)
        return mid;
    else if(mid_compare > 0)
        return mySqrt_recursion(x, start, mid);
    else
        return mySqrt_recursion(x, mid, end);

}


int mySqrt(int x)
{
    if(x <= 0) return 0;
    return mySqrt_recursion(x, 1, x);

}

/* 1017 - 0(<100%) -5.7MB, on Jan 9th, 2022 */

