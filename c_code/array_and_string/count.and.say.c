#define LEN 10000

char* doCountAndSay(char* input)
{
    char current_num;
    int index, i, count = 1;

    //printf("input %s\n", input);
    char* new = (char*)calloc(LEN, sizeof(char));
    int size = strlen(input);

    index = 0;
    current_num = input[0];
    for(i = 1; i <= size; i++)
    {
        //printf("[%d]%c-%d\n", i, current_num, count);
        if(current_num == input[i])
            count++;
        if(current_num != input[i] || input[i] == '\0')
        {
            new[index++] = count + 0x30;
            //if(count > 70) printf("count: %d\n", count);
            count = 1;
            new[index++] = current_num;
            current_num = input[i];
        }
    }
    new[index] = '\0';


    if(input) free(input);

    //printf("return %s\n", new);
    return new;
}

char* countAndSay(int n)
{
    char* ret = NULL;
    
    if(n == 1)
    {
        ret = (char*)calloc(2, sizeof(char));
        ret[0] = '1';
        ret[1] = '\0';
        //printf("%s,%#x,%#x\n", ret, ret[0], ret[1]);
        return ret;
    }
    if(n == 2)
    {
        ret = (char*)calloc(3, sizeof(char));
        ret[0] = '1';
        ret[1] = '1';
        ret[2] = '\0';
        //printf("%s,%#x,%#x\n", ret, ret[0], ret[1]);
        return ret;
    }

    ret = countAndSay(n - 1);
    ret = doCountAndSay(ret);

    return ret;
}
/* 30 - 4(<61%) - 12MB, on Oct 21st, 2021 */
