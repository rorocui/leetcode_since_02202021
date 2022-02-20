#define EN 26

typedef struct 
{
    bool node_leaf;
    struct Trie * trie_node[EN];
} Trie;


Trie* trieCreate() 
{
    Trie* node = (Trie*)malloc(sizeof(Trie));
    node->node_leaf = false;
    for(int i = 0; i < EN; i++)
        node->trie_node[i] = NULL;

    return node;
}

void trieInsert(Trie* obj, char * word) 
{
    int i;
    int len;
    int idx = 0;

    len = strlen(word);
    for(i = 0; i < len; i++)
    {
        idx = word[i] - 'a';
        if(obj->trie_node[idx])
        {
            obj = obj->trie_node[idx];
        }
        else
        {
            obj->trie_node[idx] = trieCreate();
            obj = obj->trie_node[idx];
        }
    }
    obj->node_leaf = true;
}

bool trieSearch(Trie* obj, char * word) 
{
    int i;
    int len;
    int idx = 0;

    len = strlen(word);
    for(i = 0; i < len; i++)
    {
        idx = word[i] - 'a';
        if(obj->trie_node[idx])
        {
            obj = obj->trie_node[idx];
        }
        else
            return false;
    }

    /* As I analyse, I don't think we need check obj is NULL or not;
     * since that is always not NULL to reach here 
    return(obj && obj->node_leaf); */
    return(obj->node_leaf);
}

bool trieStartsWith(Trie* obj, char * prefix)
{
    int i;
    int len;
    int idx = 0;

    len = strlen(prefix);
    for(i = 0; i < len; i++)
    {
        idx = prefix[i] - 'a';
        if(obj->trie_node[idx])
            obj = obj->trie_node[idx];
        else
            return false;
    }

    /* As my understanding, the search startsWith 'prefix' in a trie with 'prefix' stored,
     * That would return True; so don't need check node_leaf boolean here. */
    return true;

  
}

void trieFree(Trie* obj) 
{
    for(int i = 0; i < EN; i++)
        if(obj->trie_node[i])
        {
            trieFree(obj->trie_node[i]);
        }
    free(obj);
}

/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);
 
 * bool param_2 = trieSearch(obj, word);
 
 * bool param_3 = trieStartsWith(obj, prefix);
 
 * trieFree(obj);
*/

/* 15 - 83(<54%) - 39MB, on Feb 20th, 2022 */
