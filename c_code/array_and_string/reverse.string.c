int reverse(int x)
{

    int ret = 0;
    
    while(x != 0)
    {
        ret = ret * 10 + (x % 10);
        x /= 10;
        //printf("x=%d, ret=%d\n", x, ret);
        if(x != 0 && ((long)ret * 10 > INT_MAX || (long)ret * 10 < INT_MIN))
        {
            ret = 0;
            break;
        }
    }
    
    return ret;
}
/* 1032 - 6(<14%) - 5.6MB, on Oct 10th, 2021 */
