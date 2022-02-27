
#define EN 26
#define WORD_LEN 1000

typedef struct {
    struct Trie* tree_node[EN];
    bool word_end;
} Trie;

Trie* createTrie()
{
    Trie* node = (Trie*)malloc(sizeof(Trie));

    node->word_end = false;
    for(int i = 0; i < EN; i++)
        node->tree_node[i] = NULL;

    return node;
}

void insertTrieNode(Trie* obj, char* word)
{
    int i, len, idx;

    len = strlen(word);
    //printf("insert %s\n", word);
    for(i = 0; i < len; i++)
    {
        idx = word[i] - 'a';
        if(obj->tree_node[idx])
            obj = obj->tree_node[idx];
        else
        {
            obj->tree_node[idx] = createTrie();
            obj = obj->tree_node[idx];
        }
    }
    //printf("word end %#x(%c)\n", obj, idx + 'a');
    obj->word_end = true;
}

int searchShortestPrefix(Trie* obj, char* word)
{
    int i, len, idx, ret;

    ret = 0;
    len = strlen(word);
    //printf("word %s(len=%d)\n", word, len);
    for(i = 0; i < len; i++)
    {
        //printf("%#x-%c\n", word[i], word[i]);
        idx = word[i] - 'a';
        if(obj->tree_node[idx])
        {
            ret++;
            //printf("obj-%#x\n", obj);
            obj = obj->tree_node[idx];
            if(obj->word_end)
                break;
            /*
            {
                printf("word end: shortest prefix is %d\n", ret);
                return ret;
            }
            */
        }
        else
        {
            ret = 0;
            break;
        }
    }
    //printf("shortest prefix is %d\n", ret);
    return ret;
}

void freeTrie(Trie* obj)
{
    if(!obj) return;
    for(int i = 0; i < EN; i++)
    {
        if(obj->tree_node[i])
            freeTrie(obj->tree_node[i]);
    }
    free(obj);
}

char * replaceWords(char ** dictionary, int dictionarySize, char * sentence)
{
    int i, word_idx, sen_len, idx, shortest_len; 
    char* ret;
    Trie* trie_node;
    char* word;


    sen_len = strlen(sentence);
    //printf("input sentence is %s(%d)\n", sentence, sen_len);
    //printf("4th, %c\n", sentence[4]);
    word_idx = idx = shortest_len = 0;
    ret = (char*)calloc(sen_len + 2, sizeof(char));
    word = (char*)malloc(WORD_LEN * sizeof(char));
    trie_node = createTrie();

    for(i = 0; i < dictionarySize; i++)
    {
        insertTrieNode(trie_node, dictionary[i]);
    }

    for(idx = 0; idx < sen_len; idx++)
    {
        i = 0;
        while(idx < sen_len && sentence[idx] != ' ')
        {
            //printf("[%d]-%c vs [%d]-%c\n", i, word[i], idx, sentence[idx]);
            word[i++] = sentence[idx++];
        }
        word[i] = 0;
        //printf("parse word from sen - %s\n", word);
        shortest_len = searchShortestPrefix(trie_node, word);
        if(shortest_len != 0)
        {
            strncpy(&ret[word_idx], &sentence[idx - i], shortest_len);
            word_idx += shortest_len;
            if(idx < sen_len) ret[word_idx++] = ' ';
        }
        else
        {
            strncpy(&ret[word_idx], &sentence[idx - i], i);
            word_idx += i;
            if(idx < sen_len) ret[word_idx++] = ' ';
        }
        //printf("ret-%s(%d)\n\n", ret, word_idx);
    }
    ret[++word_idx] = 0;

    freeTrie(trie_node);
    free(word);

    return ret;

}
/* 126 - 40ms - 50MB, on Feb 26th, 2022 */` 
