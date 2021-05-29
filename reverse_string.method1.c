void reverseString(char* s, int sSize)
{
    char temp;
    int i;
    
    if(sSize == 1) return; 
    
    temp = *s;
    s[0] = s[sSize - 1];
    for(i = sSize - 2; i >= 0; i--)
        s[i + 1] = s[i];
    s[1] = temp;
    reverseString(s + 1, sSize -1);
}

/*477 / 477 test cases passed, but took too long.*/
