//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<malloc.h>
using namespace std;
const int maxn = 10010;

struct Trie
{
    int virusid;
    Trie *nxt[130], *fail;
    void init(){
        for(int i = 0; i < 130; ++ i)
            nxt[i] = NULL;
        fail =NULL;
        virusid = 0;
    }
}root;
int N, M, Tot;
int webid = 0, Vid = 0;
char word[210], text[maxn];

void Insert(char *s, int Vid){
    int index;
    Trie *now = &root, *tmp;
    while(*s){
        index = *s;
        if(now->nxt[index] == NULL){
            tmp = (Trie*) malloc(sizeof(Trie));
            tmp->init();
            now->nxt[index] = tmp;
        }
        now = now->nxt[index];
        ++ s;
    }
    now->virusid = Vid;
}

void Get_fail(){
    queue<Trie*> Q;
    Q.push(&root);
    Trie *now, *ancestor;
    while(!Q.empty()){
        now = Q.front();
        Q.pop();
        for(int i = 0; i < 130; ++ i){
            if(now->nxt[i]){
                Q.push(now->nxt[i]);
                if(now == &root){
                    now->nxt[i]->fail = now;
                    continue;
                }
                ancestor = now->fail;
                while(ancestor){
                    if(ancestor->nxt[i]){
                        now->nxt[i]->fail = ancestor->nxt[i];
                        break;
                    }
                    ancestor = ancestor->fail;
                }
                if(!ancestor)
                    now->nxt[i]->fail = &root;
            }
        }
    }
}

void AC_Automation(char *s){
    //Get_fail();
    Trie *now = &root, *match;
    int index;
    vector<int> ans;
    queue<pair<Trie*, int> > rec;
    while(*s){
        index = *s;
        while(!now->nxt[index] && now != &root)
            now = now->fail;
        now = now->nxt[index];
        if(!now)now = &root;
        match = now;
        while(match && match->virusid >= 0 /* && match->finish >= 0*/){
            if(match->virusid)
                ans.push_back(match->virusid);
            rec.push(make_pair(match, match->virusid));
            match->virusid = -1;
            match = match->fail;
        }
        ++ s;
    }
    while(!rec.empty()){
        rec.front().first->virusid = rec.front().second;
        rec.pop();
    }
    if(!ans.size())return;
    printf("web %d: ", webid);
    sort(ans.begin(), ans.end());
    printf("%d", ans[0]);
    for(int i = 1; i < ans.size(); ++ i)
        printf(" %d", ans[i]);
    printf("\n");
    ans.clear();
    ++ Tot;
}

int main(){
    scanf("%d", &N);
    root.init();
    while(N--){
        scanf("%s", word);
        Insert(word, ++ Vid);
    }
    Get_fail();
    scanf("%d", &M);
    while(M--){
        scanf("%s", text);
        ++ webid;
        AC_Automation(text);
    }
    printf("total: %d\n", Tot);
    return 0;
}

/**

3
aaa
bbb
ccc
2
aaabbbccc
bbaacc

*/