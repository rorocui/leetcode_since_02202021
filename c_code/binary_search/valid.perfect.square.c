bool isPerfectSquare(int num)
{
    int start, end, mid;
    int temp;

    temp = 1;
    start = 1;
    end = num;
    mid = start + (end - start) / 2;
    
    if(num == 1) return true;
    
    while(start <= end)
    {
       temp = num / mid;
       //printf("s-%d,e-%d,m-%d,temp=%d\n", start, end, mid, temp);
       if(temp == mid)
       {
           if(temp * temp == num)
                return true;
           else
                return false;
       }
        else if(temp > mid)
        {
            /* Based on constraints, temp won't equal temp1 */
            if(mid == num) return false;
            if(temp < (num / (mid + 1)))
                return false;
            else 
                start = mid + 1;
        }
        else  
        {
            if(mid > 1 && temp <= (num / (mid - 1)))
                end = mid - 1;
            else
                return false;
        }
        mid = start + (end - start) / 2;
    }
    return false;
    

}
/* 70 - 0(<100) -5.6MB, on Jan 26th, 2022 */
