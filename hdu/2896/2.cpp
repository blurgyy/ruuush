#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<malloc.h>
using namespace std;
const int maxn = 10010;

struct Trie
{
    int id;
    Trie *nxt[130], *fail;
    void init(){
        for(int i = 0; i < 130; ++ i)
            nxt[i] = NULL;
        fail = NULL;
        id = 0;
    }
}root;
int N, M, Total;
char word[210], text[maxn];

void Insert(char *s, int ID){
    Trie *now = &root, *tmp;
    while(*s){
        if(now->nxt[*s] == NULL){
            tmp = (Trie*) malloc(sizeof(Trie));
            tmp->init();
            now->nxt[*s] = tmp;
        }
        now = now->nxt[*s];
        ++ s;
    }
    now->id = ID;
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

vector<int> Find(char *s){
    //Get_fail();
    vector<int> ret;
    queue<pair<Trie*, int> > rec;
    Trie *now = &root, *match;
    while(*s){
        while(!now->nxt[*s] && now != &root)
            now = now->fail;
        now = now->nxt[*s];
        if(!now)now = &root;
        match = now;
        while(match && match->id >= 0){
            if(match->id){
                ret.push_back(match->id);
                rec.push(make_pair(match, match->id));
                match->id = -1;
            }
            match = match->fail;
        }
        ++ s;
    }
    while(!rec.empty()){
        rec.front().first->id = rec.front().second;
        rec.pop();
    }
    return ret;
}

int main(){
    root.init();
    Total = 0;
    scanf("%d", &N);
    for(int i = 0; i < N; ++ i){
        scanf("%s", word);
        Insert(word, i+1);
    }
    Get_fail();
    scanf("%d", &M);
    for(int i = 0; i < M; ++ i){
        scanf("%s", text);
        vector<int> ans = Find(text);
        int len = ans.size();
        if(!len)continue;
        //printf("size = %d\n", len);
        ++ Total;
        printf("web %d: ", i+1);
        sort(ans.begin(), ans.end());
        printf("%d", ans[0]);
        for(int i = 1; i < len; ++ i)
            printf(" %d", ans[i]);
        printf("\n");
    }
    printf("total: %d\n", Total);
    return 0;
}