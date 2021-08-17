char * addBinary(char * a, char * b)
{
    char* out = NULL;
    char* ret = NULL;
    int size;
    int i;
    int size_a, size_b, delta, small_size;
    int regrouping = 0;
    char *longer, *shorter;

    size_a = strlen(a);
    size_b = strlen(b);
    size = (size_a > size_b) ? size_a + 2 : size_b + 2;
    out = (char*)calloc(size, sizeof(char));
    
    delta = abs(size_a - size_b);
    if(size_a < size_b)
    {
        longer = b;
        shorter = a;
        small_size = size_a;
    }
    else
    {
        longer = a;
        shorter = b;
        small_size = size_b;
    }

    for(i = small_size - 1; i >= 0; i--)
    {
        switch(shorter[i] + longer[i + delta] + regrouping - 0x30 * 2)
        {
            case 3:
               out[i + delta + 1] = '1'; 
               break;
            case 2:
               regrouping = 1;
               out[i + delta + 1] = '0'; 
               break;
            case 1:
               regrouping = 0;
               out[i + delta + 1] = '1'; 
               break;
            case 0:
               regrouping = 0;
               out[i + delta + 1] = '0'; 
               break;
            default:
               printf(" bits calculation failed. %d\n", (shorter[i] + longer[i + delta] + regrouping - 0x30 * 2));
        }
    }
    for(i = delta - 1; i >=0; i--)
    {
        if(longer[i] == 0x31 && regrouping == 1)
            out[i + 1] = '0';
        else
        {
            out[i + 1] = longer[i] + regrouping;
            regrouping = 0;
        }
    }
    if(regrouping == 1)
    {
        out[0] = '1';
        ret = out;
    }
    else // start with 0, need shift 
    {
        ret = (char*)calloc((size - 1), sizeof(char));
        for(i = 0; i < size - 2; i++)
            ret[i] = out[i + 1];
        free(out);
    }
    //printf("%#x,%#x,%d\n", ret, out, strlen(ret));

    return ret;
}
/* 294 - 0 (<100%) - 5.8MB, on Aug 16th, 2021 */
