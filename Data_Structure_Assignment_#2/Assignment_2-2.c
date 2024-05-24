#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26 // Assuming only lowercase English letters

typedef struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord; // True if the node represents the end of a word
} TrieNode;

// Function to create a new trie node
TrieNode *createNode()
{
    TrieNode *pNode = (TrieNode *)malloc(sizeof(TrieNode));
    if (pNode)
    {
        pNode->isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            pNode->children[i] = NULL;
        }
    }
    return pNode;
}

// Function to insert a word into the trie
void Insert(TrieNode *root, const char *key)
{
    TrieNode *crawler = root;
    while (*key)
    {
        /*
        TODO: write a traversal on the key for inserting nodes in tree
        */
        // key값에 해당하는 index에 위치하는 children으로 crawler를 옮기기 위한 과정입니다.
        int index = (*key) - 'a';
        if (crawler->children[index] == NULL)
        {
            crawler->children[index] = createNode();
        }
        crawler = crawler->children[index];
        key++;
    }
    crawler->isEndOfWord = true;
}

// Function to search a word in the trie
bool search(TrieNode *root, const char *key)
{
    TrieNode *crawler = root;
    while (*key)
    {
        /*
        TODO: write a traversal on the key for searching nodes in tree
        */
        crawler = crawler->children[(*key) - 'a'];
        if (crawler == NULL)
        {
            return false;
        }
        key++;
    }
    return (crawler != NULL && crawler->isEndOfWord);
}
bool isEmpty(TrieNode *root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

bool deleteHelper(TrieNode *root, const char *key, int depth)
{
    if (!root)
    {
        return false;
    }

    // If last character of key is being processed
    if (*key == '\0')
    {
        if (root->isEndOfWord)
        {
            root->isEndOfWord = false;
            // If root does not have any children (its not prefix of any other word)
            if (isEmpty(root))
            {
                return true; // Delete the node
            }
            return false; // Do not delete the node
        }
    }
    else
    {
        int index = *key - 'a';
        if (root->children[index])
        {
            /*
            TODO: write a traversal on the key for searching nodes and deleting
            Hint: recersive solutions are always in handy
            */
            bool checker = deleteHelper(root->children[index], key + 1, depth + 1);
            // depth가 증가하고, depth를 증가시키는 새로운 deleteHelper를 호출합니다. deleteHelper는 마지막 '\0'을 만났을 때 값을 리턴할 것이고, 만약 노드를 삭제할 수 없다면 false를 리턴합니다.
            // checker는 다음 노드에 대한 정보를 가져오기에 다음 노드의 children을 free하고, 해당 노드를 NULL로 초기화합니다.
            // 이후의 checker는 노드가 endofWord가 아닌지, 비어있는지를 파악한 후 삭제 여부를 전달합니다.
            if (checker)
            {
                free(root->children[index]);
                root->children[index] = NULL;
                return !root->isEndOfWord && isEmpty(root);
            }
        }
    }
    return false;
}

void Delete(TrieNode *root, const char *key)
{
    if (root != NULL && *key && search(root, key))
    {
        deleteHelper(root, key, 0);
    }
    else
    {
        printf("Cannot delete '%s': Word not found in Trie.\n", key);
    }
}

void modify(TrieNode *root, const char *oldKey, const char *newKey)
{
    Delete(root, oldKey);
    Insert(root, newKey);
}
void suggestions(TrieNode *root, const char *currentPrefix)
{
    if (root->isEndOfWord)
    {
        printf("%s\n", currentPrefix);
    }

    if (isEmpty(root))
    {
        return;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            /*
            TODO: write a traversal on the prefix for searching nodes and completing
            Hint: recersive solutions are always in handy
            */
            int lenStr = strlen(currentPrefix);
            char *temp = (char *)malloc((lenStr + 2) * sizeof(char));
            int tmpIndex = 0;
            while (currentPrefix[tmpIndex])
            {
                temp[tmpIndex] = currentPrefix[tmpIndex];
                tmpIndex++;
            }
            temp[lenStr++] = i + 'a';
            // 기존 복제에서 마지막 자리 '\0'을 대체합니다. 그런 다음 그 다음 자리를 다시 '\0'으로 변경합니다.
            temp[lenStr++] = '\0';
            suggestions(root->children[i], temp);
            free(temp);
            // 재귀적으로 root 다음 알파벳이 trie에 있다면, 해당 문자까지 prefix로 보는 것입니다. 그렇게 되면 모든 문자를 출력할 수 있게 됩니다.
        }
    }
}

void autoComplete(TrieNode *root, const char *prefix)
{
    TrieNode *crawler = root;
    for (int i = 0; prefix[i] && crawler; i++)
    {
        int index = prefix[i] - 'a';
        crawler = crawler->children[index];
    }

    if (crawler)
    {
        suggestions(crawler, prefix);
    }
}
#include <stdio.h>
#include <stdlib.h>

int main()
{
    TrieNode *root = createNode(); // Initialize the Trie

    // Predefined words to insert into the Trie
    char *wordsToInsert[] = {"apple", "app", "application", "apricot", "banana",
                             "berry", "blueberry", "blackberry", "banana", "balm", "ba"};
    int n = sizeof(wordsToInsert) / sizeof(wordsToInsert[0]);

    // Inserting words into the Trie
    for (int i = 0; i < n; i++)
    {
        Insert(root, wordsToInsert[i]);
        printf("Inserted: %s\n", wordsToInsert[i]);
    }
    /*
    Inserted: apple
    Inserted: app
    Inserted: application
    Inserted: apricot
    Inserted: banana
    Inserted: berry
    Inserted: blueberry
    Inserted: blackberry
    Inserted: banana
    Inserted: balm
    Inserted: ba
    */

    // Perform an autocomplete on 'app'
    printf("Autocomplete results for 'app':\n");
    autoComplete(root, "app");
    /*
    Autocomplete results for 'app':
    app
    apple
    application
    */

    // Perform an autocomplete on 'ba'
    printf("Autocomplete results for 'ba':\n");
    autoComplete(root, "ba");
    /*
    Autocomplete results for 'ba':
    ba
    balm
    banana
    */

    // Modifying 'banana' to 'bandana'
    modify(root, "banana", "bandana");
    printf("Modified 'banana' to 'bandana'.\n");

    // Perform an autocomplete on 'ba'
    printf("Autocomplete results for 'ba':\n");
    autoComplete(root, "ba");
    /*
    Autocomplete results for 'ba':
    ba
    balm
    bandana
    */

    // Cleaning up the Trie
    for (int i = 0; i < n; i++)
    {
        Delete(root, wordsToInsert[i]);
    }
    Delete(root, "bandana"); // Deleting the modified word
                             /*
                             Cannot delete 'banana': Word not found in Trie.
                             Cannot delete 'banana': Word not found in Trie.
                             */

    return 0;
}
