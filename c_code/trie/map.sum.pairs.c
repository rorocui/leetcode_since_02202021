#define EN 26

typedef struct 
{
    int val;
    struct MapSum *tree_node[EN];
    
} MapSum;


MapSum* mapSumCreate() 
{
    MapSum *node = (MapSum*)malloc(sizeof(MapSum));

    node->val = 0;
    for(int i = 0; i < EN; i++)
        node->tree_node[i] = NULL;

    //printf("malloc-%#x\n", node);
    return node;
}

void mapSumInsert(MapSum* obj, char * key, int val) 
{
    int i;
    int len;
    int idx = 0;

    len = strlen(key);
    for(i = 0; i < len; i++)
    {
        idx = key[i] - 'a';
        if(obj->tree_node[idx])
            obj = obj->tree_node[idx];
        else
        {
            //printf("[%d]\n", idx);
            obj->tree_node[idx] = mapSumCreate();
            obj = obj->tree_node[idx];
        }
    }
    obj->val = val;
    //printf("(%#x)obj->val-%d\n", obj, obj->val);
}

int mapSumRecursion(MapSum* obj)
{
    int i;
    int sum;
    MapSum* temp = NULL;
    
    //printf("%s:%#x\n", __func__, obj);
    
    sum = obj->val;
    //printf("sum-%d\n", sum);
    
    for(i = 0; i < EN; i++)
        if(obj->tree_node[i])
        {
            //printf("[%d]-%#x\n", i, obj->tree_node[i]);
            temp = obj->tree_node[i];
            //sum += temp->val;
            /* dereferencing problem */
            //sum += obj->tree_node[i]->val;
            sum += mapSumRecursion(temp);
            //printf("[%d]-%d\n", i, sum);    
        }

    return sum;
}

int mapSumSum(MapSum* obj, char * prefix) 
{
    int i;
    int len;
    int idx = 0;

    len = strlen(prefix);
    for(i = 0; i < len; i++)
    {
        idx = prefix[i] - 'a';
        if(obj->tree_node[idx])
        {
            //printf("search idx-%d\n", idx);
            obj = obj->tree_node[idx];
        }
        else
            return 0;
    }
    
    return mapSumRecursion(obj);
}

void mapSumFree(MapSum* obj) 
{
    int i;

    for(i = 0; i < EN; i++)
        if(obj->tree_node[i])
            mapSumFree(obj->tree_node[i]);

    free(obj);
}
/* 35 - 0(<100%) - 6.7MB, on Feb 22nd, 2022 */

/**
 * Your MapSum struct will be instantiated and called as such:
 * MapSum* obj = mapSumCreate();
 * mapSumInsert(obj, key, val);
 
 * int param_2 = mapSumSum(obj, prefix);
 
 * mapSumFree(obj);
*/

