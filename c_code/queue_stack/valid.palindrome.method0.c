bool isPalindrome(char * s)
{
    int size, right, left, i, counter; 
    bool ret;

    left = right = size = counter = 0;

    /* count size of string by lowcase charactor */
    for(i = 0; i < strlen(s); i++)
        if((s[i] >= 0x61 && s[i] <= 0x7A) || (s[i] >= 0x30 && s[i] <= 0x39))
            size++;
        else if(s[i] >= 0x41 && s[i] <= 0x5A)
        {
            s[i] += 0x20;
            size++;
        }
    
    if(size <= 1) return true;
    //printf("size=%d\n", size);

    for(i = 0; counter < size / 2 && i < strlen(s); i++) 
        if((s[i] >= 0x61 && s[i] <= 0x7A) || (s[i] >= 0x30 && s[i] <= 0x39))
        {
            counter++;
        }
    if(counter != size / 2) return false;
    left = i - 1;

    /* remove middle one if odd size */
    if(size % 2 == 1)
    {
        while(! ((s[i] >= 0x61 && s[i] <= 0x7A) || (s[i] >= 0x30 && s[i] <= 0x39)))
            i++;
        i++;
    }
    right = i;
    
    //printf("left=%d,right=%d\n", left, right);
    /* scan from the middle */ 
    for(left, right; left >= 0 && right < strlen(s);)
    {
        while(left >= 0 && !((s[left] >= 0x61 && s[left] <= 0x7A) || (s[left] >= 0x30 && s[left] <= 0x39)))
            left--;
        while(right < strlen(s) && !((s[right] >= 0x61 && s[right] <= 0x7A) || (s[right] >= 0x30 && s[right] <= 0x39)))
            right++;
        if(left < 0 || right >= strlen(s))
            break;
        //printf("%c vs %c\n", s[left], s[right]);
        if(s[left] != s[right])
            return false;
        left--;
        right++;
    }
    return true;

}
/* 480 - 164(n/a) - 6.3MB, on Oct 17th, 2021 */

