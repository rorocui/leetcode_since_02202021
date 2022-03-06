#define EN 26

typedef struct worddictionary {
    struct worddictionary* trie_node[26];
    bool leaf_node;

} WordDictionary;


WordDictionary* wordDictionaryCreate()
{
   WordDictionary* node = (WordDictionary*)calloc(1, sizeof(WordDictionary));
   /* 
   node->leaf_node = false;
   for(int i = 0; i < 26; i++)
       node->trie_node[i] = NULL;
    */
   return node;
}

void wordDictionaryAddWord(WordDictionary* obj, char* word)
{
    while(*word)
    {
        if(obj->trie_node[*word - 'a'])
            obj = obj->trie_node[*word - 'a'];
        else
        {
            obj = obj->trie_node[*word - 'a'] = wordDictionaryCreate();
        }
        word++;
    }
    obj->leaf_node = true;
}


bool wordDictionarySearch(WordDictionary* obj, char* word)
{
    int i;

    while(*word)
    {
        if(*word == '.')
        {
            for(i = 0; i < EN; i++)
                if(obj->trie_node[i])
                    if(wordDictionarySearch(obj->trie_node[i], word + 1))
                            return true;
            return false;
        }
        else if(! obj->trie_node[*word - 'a'])
            return false;
        obj = obj->trie_node[*word - 'a'];
        word++;
    }

    if(obj->leaf_node)
        return true;
    else
        return false;
}

void wordDictionaryFree(WordDictionary* obj)
{
    for(int i = 0; i < 26; i++)
        if(obj->trie_node[i])
            wordDictionaryFree(obj->trie_node[i]);
    free(obj);
}
/* 29 - 1231(<7%) - 490.4MB, on March 5th, 2022 */
