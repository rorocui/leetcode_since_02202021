void reverseString(char* s, int sSize)
{
    int i = 0;
    int j = sSize - 1;
    char temp;

    while(i < j)
    {
        //printf("%d,%d,%d\n", i, j, sSize);
        temp = s[i];
        s[i++] = s[j];
        s[j--] = temp;
    }
}


/* recursion: 477 test cases in 52ms(<32%), in 12.6MB, on May 28th, 2021 */
/* two pointers: 477 - 44(<93%) - 12.3MB, on Aug 19th, 2021 */
