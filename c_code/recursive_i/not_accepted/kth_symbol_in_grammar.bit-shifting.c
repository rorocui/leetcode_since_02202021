long grammar(long input, int len)
{
    int i;
    long ret;
    long tmp;


    printf("input=%ld, len=%d\n", input, len);
    ret = 0;
    for(i = len - 1; i >= 0; i--)
    {
        tmp = (input >> i) & 0x01;
        printf("bit:0x%x\n", tmp);
        if(tmp == 0)
        {
            ret = (ret | 0x01);
            //printf("0:%#x\n", ret);
        }
        else
        {
            //printf("1b:%#x\n", ret);
            ret = (ret | 0x02);
            //printf("1a:%#x\n", ret);
        }
        //printf("[%d]%d\n", i, ret);
        if(i > 0) 
        {
            ret = ret << 2;
            printf("i>0: %#x:%d\n", ret, len);
        }
    }

    printf("%#x:%d\n", ret, len);
    return ret;
}

long nGrammar(int n)
{
    if(n == 1) return 0;

    return grammar(nGrammar(n - 1), (int)pow(2.0, n - 2));
}


int kthGrammar(int n, int k)
{
    printf("%d,%d\n", sizeof(int), sizeof(long));
    long nth = 0;
    int ret = 0;

    nth = nGrammar(n);
    printf("%#x\n", nth);

    ret = (int)((nth >> ((int)pow(2.0, n - 1) - k)) & 0x01);

    return ret; 
}


/* failed on 15/55 */
