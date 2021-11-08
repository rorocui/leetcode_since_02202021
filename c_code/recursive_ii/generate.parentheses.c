#include <string.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */


#define LEN 2000

static int ret_index;

void gen_parenthesis_bt(char** ret, char* new, int n, int* idx, int open, int close)
{
    //printf("{%d}[%d]%s\n", ret_index, *idx, new);
    if(strlen(new) == 2*n)
    {
        ret[ret_index] = (char*)calloc((2 * n + 1), sizeof(char));
        strcpy(ret[ret_index++], new);
        //printf("..{%d}[%d]%s\n", ret_index, *idx, ret[ret_index - 1]);
    }
    if(open < n)
    {
        new[(*idx)++] = '(';
        gen_parenthesis_bt(ret, new, n, idx, open + 1, close);
        new[*idx] = '\0';
        (*idx)--;
    }
    //printf("%d vs %d\n", open, close);
    if(close < open)
    {
        new[(*idx)++] = ')';
        gen_parenthesis_bt(ret, new, n, idx, open, close + 1);
        new[*idx] = '\0';
        (*idx)--;
    }
    //printf("[%d]return %d vs %d\n", *idx, open, close);
    
}


char ** generateParenthesis(int n, int* returnSize)
{
    char** ret = NULL;
    int i, idx;
    char* temp = NULL;


    ret_index = 0;
    ret = (char**)malloc(LEN * sizeof(char*));
    temp = (char*)calloc(2 * n + 1, sizeof(char));

    gen_parenthesis_bt(ret, temp, n, &idx, 0, 0);

    *returnSize = ret_index;

    if(temp) free(temp);

    return  ret;
}
/* 8 - 0 (<100%) - 11.9MB, on Nov 7th, 2021 */
