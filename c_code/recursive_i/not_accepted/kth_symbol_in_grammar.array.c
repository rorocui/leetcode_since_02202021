
void grammar(int* out, int* in, int len)
{
    //printf("%s:%#x,%#x,%d\n", __func__, out, in, len);
    int i;
    int idx = 0;

    for(i = 0; i < len; i++)
    {
        if(in[i] == 0)
        {
            out[idx++] = 0;
            out[idx++] = 1;
        }
        else
        {
            out[idx++] = 1;
            out[idx++] = 0;
        }

    }
}

int power_two(int n)
{
    return (int)pow(2.0, n);
}

void nGrammar(int* ret, int n)
{
    
    //printf("%s:%#x,%d\n", __func__, ret, n);
    int* out = NULL;

    if(n == 1)
    {
        ret[0] = 0;
        return;
    }
    out = (int*)calloc(power_two(n - 2), sizeof(int));
    nGrammar(out, n - 1);
    grammar(ret, out, power_two(n - 2)); 
    free(out);
}


int kthGrammar(int n, int k)
{
    int* ret = NULL;

    ret = (int*)calloc(power_two(n - 1), sizeof(int));
    nGrammar(ret, n);

    return ret[k - 1]; 
}


/* failed on 15/55  : Memory Limit Exceeded on Aug 6th, 2021 */
