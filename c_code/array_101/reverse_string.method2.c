void reverseString(char* s, int sSize)
{
    char temp;
    int i;
    
    if(sSize == 1) return; 
    if(sSize == 2)
    {
        temp = s[0];
        s[0] = s[1];
        s[1] = temp;
        return;
    }
    
    temp = *s;
    s[0] = s[sSize - 1];
    s[sSize - 1] = temp;
    reverseString(s + 1, sSize - 2);
}

/* 477 test cases in 52ms(<32%), in 12.6MB, on May 28th, 2021 */
