bool isPalindrome(char * s)
{
    int right, left, size;

    left = 0;
    size = right = strlen(s) - 1;

    /* scan from two ends to the middle */ 
    while(left < right)
    {
        while(left <= size \
                && !((s[left] >= 'a' && s[left] <= 'z') \
                || (s[left] >= '0' && s[left] <= '9') \
                || (s[left] >= 'A' && s[left] <= 'Z')))
            left++;
        while(right >= 0 \
                && !((s[right] >= 'a' && s[right] <= 'z') \
                || (s[right] >= '0' && s[right] <= '9') \
                || (s[right] >= 'A' && s[right] <= 'Z')))
            right--;
        if(left >= right)
            break;
        //printf("[%d]%c vs [%d]%c\n", left, right, s[left], s[right]);
        if(s[left] >= 'A' && s[left] <= 'Z')
            s[left] += 0x20;
        if(s[right] >= 'A' && s[right] <= 'Z')
            s[right] += 0x20;
        if(s[left] != s[right])
            return false;
        left++;
        right--;
    }
    return true;

}
/* method.0 -  480 - 164(n/a) - 6.3MB, on Oct 17th, 2021 */
/* method.1 -  480 - 0(<100%) - 6.5MB, on Oct 17th, 2021 */
