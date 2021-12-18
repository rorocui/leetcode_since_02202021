int combination_size(char* digits, int* len)
{
    //printf("%s, first character =%#x\n", __func__, digits[0]);
    int size = 1;

    *len = 0;

    while(digits && digits[*len] != '\0')
    {
        if(digits[*len] == 0x39 || digits[*len] == 0x37)
            size *= 4;
        else if(digits[*len] >= 0x32 && digits[*len] <= 0x36 || digits[*len] == 0x38)
            size *= 3;
        else
        {
            printf("input digit is invalid, %#x\n", digits[*len]);
            return -1;
        }
        (*len)++;
        if(*len > 4)
        {
            printf("input digits len is invalid, %d\n", *len);
            return -2;
        }
    }

    return size;
}

int letter_decider(char digit)
{
    //printf("%s:%c\n", __func__, digit);
    if(digit == '9')
        return 0x77;
    else if (digit == '7')
        return 0x70;
    else if (digit == '8')
        return 0x74;
    else
        return 0x61 + (3 * ((int)(digit - 0x31) - 1));

}

/* ASCII table, 'a' = 0x61, 'z' = 0x7A */
void letter_combine_recursion(char** ret, int* idx, char* digits, int len, char* tmp_buff, int tmp_size)
{
    int i;
    int starter = 0;
    
    /* debug code 
    printf("tmp_buff[len=%d]: ", tmp_size);
    for(int m = 0; m < tmp_size; m++)
        printf("%c ", tmp_buff[m]);
    printf("\n");
    */
    if(len == tmp_size)
    {
        memcpy(ret[(*idx)++], tmp_buff, (len + 1) * sizeof(char));
        /*
        printf("ret[%d]: ", *idx - 1);
        for(int m = 0; m < tmp_size; m++)
            printf("%c ", ret[*idx - 1][m]);
        printf("\n");
        */
    }
    else
    {
        starter = letter_decider(digits[tmp_size]);
        //printf("%#x\n", starter);
        for(i = 0; i < 3; i++)
        {
            tmp_buff[tmp_size] = starter + i;
            letter_combine_recursion(ret, idx, digits, len, tmp_buff, tmp_size + 1);
            if((starter == 0x77 || starter == 0x70) && i == 2)
            {
                tmp_buff[tmp_size] = starter + 3;
                letter_combine_recursion(ret, idx, digits, len, tmp_buff, tmp_size + 1);
            }
        }
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** letterCombinations(char * digits, int* returnSize)
{
    
    int i;
    char** ret = NULL;
    char* tmp_buf = NULL;
    int len = 0;
    int idx = 0;

    *returnSize = combination_size(digits, &len);
    if(len == 0)
    {
        *returnSize = 0;
        return NULL;
    }


    ret = (char**)malloc(*returnSize * sizeof(char*));
    for(i = 0; i < *returnSize; i++)
        ret[i] = (char*)calloc(len + 1, sizeof(char));
    tmp_buf = (char*)calloc(len + 1, sizeof(char));

    letter_combine_recursion(ret, &idx, digits, len, tmp_buf, 0);

    if(tmp_buf) free(tmp_buf);

    return ret;
}
/* 25 - 0 (<100%) - 6MB, on Dec 17th, 2021 */

