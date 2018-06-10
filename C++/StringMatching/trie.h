#ifndef TRIE_H
#define TRIE_H
#include <list>
#include <iostream>
#include <vector>
#include <QString>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

char *to_char(string str){
    char* charpoint = new char[str.length()+1];
    strcpy(charpoint,str.c_str());
    return charpoint;
}
/*
if((text[i]<'0'||text[i]>'z')||(text[i]>'9'&&text[i]<'A')||(text[i]>'Z'&&text[i]<'a')) return 0;
else {if(text[i]>='0'&&text[i]<='9')
returntext[i] - '0';
else if(text[i]>='A'&&text[i]<='Z')
    ind=text[i]+32-'0'-40;
else ind=text[i] - '0'-40;
*/

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

// Alphabet size (# of symbols)

#define ALPHABET_SIZE (35)
int INDEX(char c){
    if((c<'0'||c>'z')||(c>'9'&&c<'A')||(c>'Z'&&c<'a')) return 0;
    else if(c>='0'&&c<='9')
        return c - '0';
    else if(c>='A'&&c<='Z')
        return c+32-'0'-40;
    else return c - '0'-40;
}

#define FREE(p) \
    free(p);    \
    p = NULL;

// forward declration
typedef struct trie_node trie_node_t;

// trie node
struct trie_node
{
    int value; // non zero if leaf
    trie_node_t *children[ALPHABET_SIZE];
};

// trie ADT
typedef struct trie trie_t;

struct trie
{
    trie_node_t *root;
    int count;
};

trie_node_t *getNode(void)
{
    trie_node_t *pNode = static_cast<trie_node_t *>(malloc(sizeof(trie_node_t)));

    if( pNode )
    {
        int i;

        pNode->value = 0;

        for(i = 0; i < ALPHABET_SIZE; i++)
        {
            pNode->children[i] = NULL;
        }
    }

    return pNode;
}

void initialize(trie_t *pTrie)
{
    pTrie->root = getNode();
    pTrie->count = 0;
}

void insert(trie_t *pTrie, char *key)
{
    uint level;
    uint length = strlen(key);
    int index;
    trie_node_t *pCrawl;

    pTrie->count++;
    pCrawl = pTrie->root;

    for( level = 0; level < length; level++ )
    {
        index = INDEX(key[level]);
        //cout<<index<<endl;
        if( pCrawl->children[index] )
        {
            // Skip current node
            pCrawl = pCrawl->children[index];
        }
        else
        {
            // Add new node
            pCrawl->children[index] = getNode();
            pCrawl = pCrawl->children[index];
        }
    }

    // mark last node as leaf (non zero)
    pCrawl->value = pTrie->count;
    //free(pCrawl);
    //delete pCrawl;
}

void initializer(trie_t *pTrie, vector<string> txt){
    pTrie->root = getNode();
    pTrie->count = 0;
    for(ulong i=0; i<txt.size();i++){
        insert(pTrie,to_char(txt[i]));
    }
}


bool trieSearch(trie_t *pTrie, char *key)
{
    uint level;
    uint length = strlen(key);
    int index;
    trie_node_t *pCrawl;

    pCrawl = pTrie->root;

    for( level = 0; level < length; level++ )
    {
        index = INDEX(key[level]);

        if( !pCrawl->children[index] )
        {
            return false;
        }

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl && pCrawl->value);
}

bool leafNode(trie_node_t *pNode)
{
    return (pNode->value);
}

bool isItFreeNode(trie_node_t *pNode)
{
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        if( pNode->children[i] )
            return false;
    }
    return true;
}

bool deleteHelper(trie_node_t *pNode, char *key, uint level, uint len)
{
    if( pNode )
    {
        // Base case
        if( level == len )
        {
            if( pNode->value )
            {
                // Unmark leaf node
                pNode->value = 0;

                // If empty, node to be deleted
                if( isItFreeNode(pNode) )
                {
                    return true;
                }

                return false;
            }
        }
        else // Recursive case
        {
            int index = INDEX(key[level]);

            if( deleteHelper(pNode->children[index], key, level+1, len) )
            {
                // last node marked, delete it
                FREE(pNode->children[index]);

                // recursively climb up, and delete eligible nodes
                return ( !leafNode(pNode) && isItFreeNode(pNode) );
            }
        }
    }

    return false;
}

void deleteKey(trie_t *pTrie, char *key)
{
    uint len = strlen(key);

    if( len > 0 )
    {
        deleteHelper(pTrie->root, key, 0, len);
    }
}

/*
//typedef pair<struct TrieNode *children[ALPHABET_SIZE]>;

class Node {
private:
    bool mMarker;
    vector<Node *> mChildren;
    char mContent;
public:
    Node(char Content){
        this->mContent=Content;
    }
    Node() {
        mContent = ' ';
        mMarker = false;
    }
    ~Node() {
        mChildren.clear();
        mChildren.~vector();
    }
    char content() { return mContent; }
    void setContent(char c) { mContent = c; }
    bool wordMarker() { return mMarker; }
    void setWordMarker() { mMarker = true; }
    Node* findChild(char c);
    void appendChild(Node* child) { mChildren.push_back(child); }
    vector<Node*> children() { return mChildren; }
};

class Trie {
public:
    Trie();
    Trie(vector<string> txt);
    ~Trie(){
        root->~Node();
        free(root);
        free(this);
    }
    void addWord(string s);
    bool searchWord(string s);
private:
    Node* root = new Node;
};

Node* Node::findChild(char c)
{
    for ( uint i = 0; i < mChildren.size(); i++ )
    {
        Node* tmp = mChildren.at(i);
        if ( tmp->content() == c )
            return tmp;
    }

    return NULL;
}
Trie::Trie()
{
    root = new Node();
}

Trie::Trie(vector<string> txt)
{
    root = new Node();
    for(ulong i=0; i<txt.size(); i++)
        addWord(txt[i]);
}

void Trie::addWord(string s)
{
    Node* current = root;

    if ( s.length() == 0 )
    {
        current->setWordMarker(); // an empty word
        return;
    }
    Node* child = nullptr;
    for ( uint i = 0; i < s.length(); i++ )
    {
        child = current->findChild(s[i]);
        if (child)
        {
            current = child;
        }
        else
        {
            //if(s[i]!='.' && s[i]!=' '){
                Node* tmp = new Node(s[i]);
                current->appendChild(tmp);
                current = tmp;
//            }else{
//                addWord(s.substr(i+1));
//            }
        }
        if (i == s.length() - 1)
            current->setWordMarker();
    }
}

bool Trie::searchWord(string s)
{
    Node* current = root;

    while (current)
    {
        for ( uint i = 0; i < s.length(); i++ )
        {
            current = current->findChild(s[i]);
            if (!current)
                return false;
        }
        return true;
    }
    return false;
}
*/
#endif
