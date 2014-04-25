// Md. Khairullah Gaurab
// SUST. CSE. 20th Batch

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <map>
#include <utility>

using namespace std;

struct Trie
{
    Trie *edges[26];
    bool word;
    int idx;
};
string currWord;
string morse[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
                   "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
                   "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
                 };
map<string, int> m;
Trie *start;
int dp[10005][1000];
int cnt;
void addWord(Trie *node, int pos)
{
    while(pos!=(int)currWord.size())
    {
        int curr = currWord[pos]-'A';
        if(node->edges[curr]==NULL)
        {
            node->edges[curr] = new Trie();
            node->idx = cnt++;
        }
        node = node->edges[curr];
        pos++;
    }
    node->word = true;
}
int rec_trie(Trie *node, int pos)
{
    if(node==NULL or pos>(int)currWord.size()) return 0;
    if(pos==(int)currWord.size()) return node->word?1:0;
    else if(dp[pos][node->idx]!=-1)
    {
        return dp[pos][node->idx];
    }
    else
    {
        int res = 0;
        int i = pos;
        if(node->word) res = rec_trie(start,pos);
        string s = "";
        while(i<pos+4)
        {
            s += currWord[i];
            if(m.find(s)!=m.end()) res += rec_trie(node->edges[m[s]],i+1);
            i++;
        }
        return dp[pos][node->idx]=res;
    }
}
int main()
{
    int T, n;
    char input[100005];
    char words[25];
    string S;
    for(int i=0; i<26; i++) m[morse[i]] = i;
    scanf("%d",&T);
    while (T--)
    {
        scanf("%s",input);
        scanf("%d",&n);
        start = new Trie();
        cnt = 0;
        for(int i=0; i<n; i++)
        {
            scanf("%s",words);
            currWord = string(words);
            addWord(start,0);
        }
        currWord = string(input);
        memset(dp,-1,sizeof(dp));
        int res = rec_trie(start,0);
        printf("%d\n",res);
        if(T>0) printf("\n");
    }
    return 0;
}
