///Nah..

#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

struct Trie{
    Trie *nxt[26];
    int id;
    bool finish;
    Trie(){
        for(int i = 0; i < 26; ++ i)
            nxt[i] = NULL;
        id = -1;
        finish = false;
    }
    void init(){
        for(int i = 0; i < 26; ++ i)
            nxt[i] = NULL;
        id = -1;
        finish = false;
    }
}root;
int n;
string in[maxn];

void insert(string &s, int id){
    int len = s.size();
    for(int i = 0; i < len; ++ i){
        int index = s[i] - 'a';
        if(!now->nxt[index])
            now->nxt[index] = new Trie;
        now = now->nxt[index];
    }
    now->finish = true;
    now->id = id;
}

void Del(Trie *now = &root){
    for(int i = 0; i < 26; ++ i){
        if(now->nxt[i]){
            Del(now->nxt[i]);
            free(now->nxt[i]);
        }
    }
}

void init(){
    Del();
    root.init();
}

int main(){
    ios_base::sync_with_stdio(false);
    while(~scanf("%d", &n)){
        init();
        for(int i = 0; i < n; ++ i){
            cin >> in[i];
            if(in[i].size() > 26){
                printf("NO\n");
                return 0;
            }
            string s = in[i];
            while(s.size()){
                insert(in[i], i);
                s = s.substr(1);
            }
        }

    }
    return 0;
}