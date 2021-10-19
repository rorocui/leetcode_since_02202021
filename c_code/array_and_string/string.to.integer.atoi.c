int myAtoi(char* s)
{
    long ret;
    int size;
    int idx;
    int factor = 1;

    size = strlen(s);
    idx = 0;
    ret = 0;

    while(s[idx] == ' ')
        idx++;
    
    if(s[idx] == '-')
    {
        factor = -1;
        idx++;
    }
    else if(s[idx] == '+')
        idx++;

    if(!(s[idx] >= '0' && s[idx] <= '9'))
        return 0;

    while(s[idx] >= '0' && s[idx] <= '9')
    {
        ret = ret*10 + s[idx] - 0x30;
        if(ret > INT_MAX && factor == 1)
            return INT_MAX;
        else if(ret > (long)INT_MAX + 1 && factor == -1)
            return INT_MIN;
        idx++;
    }

   return (int)(ret * factor); 
}
/* 1082 - 4(<61%) - 5.7MB, on Oct 18th, 2021 */
