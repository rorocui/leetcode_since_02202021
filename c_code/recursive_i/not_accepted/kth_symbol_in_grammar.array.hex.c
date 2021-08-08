void grammar(long* out, long* in, int len)
{
    //printf("%s:%#x,%#x,%d\n", __func__, out, in, len);
    int i;
    int idx = 0;

    for(i = 0; i < len; i++)
    {
        //printf("%#x\n", in[i]);
        switch (in[i])
        {
            case 0x6996966996696996:
                out[idx++] = 0x6996966996696996;
                out[idx++] = 0x9669699669969669;
                //printf("%#x\n", out[idx - 2]);
                break;
            case 0x9669699669969669:
                out[idx++] = 0x9669699669969669;
                out[idx++] = 0x6996966996696996;
                break;
            default:
                printf("error input number is invalid at [%d]%d\n", i, in[i]);
        }
    }
}

int cal_len(int n)
{
    int ret;
    
    if(n <= 7) ret = 1;
    else
        ret = (int)(pow(2.0, n - 4) / 8);    
    
    
    //printf("%s:%d\n", __func__, ret);
    return ret;
}

void nGrammar(long* ret, int n)
{
    
    //printf("%s:%#x,%d\n", __func__, ret, n);
    long* out = NULL;

    if(n == 7)
    {
        ret[0] = 0x6996966996696996;
        return;
    }
    
    out = (long*)calloc(cal_len(n - 1), sizeof(long));
    nGrammar(out, n - 1);
    //printf("%d returned\n", n - 1);
    grammar(ret, out, cal_len(n - 1)); 
    //printf("a:%#x,%d\n", ret, n);
    free(out);
}


int kthGrammar(int n, int k)
{
    long* ret = NULL;
    int shift = 0;
    int bitwidth = 64;
    
    ret = (long*)calloc(cal_len(n), sizeof(long));
    switch(n)
    {
        case 1:
            ret[0] = 0;
            shift = 1;
            break;
        case 2:
            ret[0] = 1;
            shift = 2;
            break;
        case 3:
            ret[0] = 6;
            shift = 4;
            break;
        case 4:
            ret[0] = 0x69;
            shift = 8;
            break;
        case 5:
            ret[0] = 0x6996;
            shift = 16;
            break;
        case 6:
            ret[0] = 0x69969669;
            shift = 32;
            break;
        default:    
            nGrammar(ret, n);
            //printf("[%d] returned\n", n);
            shift = bitwidth;
    }
    shift = (k % bitwidth == 0) ? 0 : (shift - k % bitwidth);

    return (ret[(k - 1) / bitwidth] >> shift) & 0x01; 
}


/* failed on 15/55  :(bitwidth = 1) Memory Limit Exceeded on Aug 6th, 2021 */
/* failed on 15/55  :(bitwidth = 8) Time Limit Exceeded on Aug 7th, 2021 */
/* failed on 27/55  :(bitwidth = 32) Time Limit Exceeded on Aug 7th, 2021 */
/* failed on 32/55  :(bitwidth = 64) Time Limit Exceeded on Aug 7th, 2021 */


