#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1010;
//const ll inf = 0x3f3f3f3f3f3f3f3f;

struct Trie{
    int finish, age, cur[10], size;
    Trie *nxt[26], *fail;
    void init(){
        finish = age = size = 0;
        for(int i = 0; i < 26; ++ i)
            nxt[i] = NULL;
        fail = NULL;
    }
}root;
int n;
ll mn[maxn], mx[maxn];
ll cnt[maxn], age[maxn];
string s[maxn];

void insert(int ii){
    int index;
    Trie *now = &root, *tmp;
    for(int i = 0; i < s[ii].size(); ++ i){
        index = s[ii][i] - 'a';
        if(!now->nxt[index]){
            tmp = (Trie*) malloc(sizeof(Trie));
            tmp->init();
            now->nxt[index] = tmp;
        }
        now = now->nxt[index];
    }
    now->finish ++;
    now->age = age[ii];
    now->cur[now->size++] = ii;
}

void Get_fail(){
    queue<Trie*> que;
    que.push(&root);
    Trie *now, *anc;
    while(!que.empty()){
        now = que.front();
        que.pop();
        for(int i = 0; i < 26; ++ i){
            if(now->nxt[i]){
                que.push(now->nxt[i]);
                if(now == &root){
                    now->nxt[i]->fail = &root;
                    continue;
                }
                anc = now->fail;
                while(anc){
                    if(anc->nxt[i]){
                        now->nxt[i]->fail = anc->nxt[i];
                        break;
                    }
                    anc = anc->fail;
                }
                if(!anc)
                    now->nxt[i]->fail = &root;
            }
        }
    }
}

void ACA(int ii){
    Trie *now = &root, *match;
    int index;
    for(int i = 0; i < s[ii].size(); ++ i){
        index = s[ii][i] - 'a';
        while(now != &root && !now->nxt[index])
            now = now->fail;
        now = now->nxt[index];
        match = now;
        if(!now)now = &root;
        while(match){
            if(match->finish){
                for(int j = 0; j < match->size; ++ j){
                    mn[match->cur[j]] = min(mn[match->cur[j]], age[ii]);
                    mx[match->cur[j]] = max(mx[match->cur[j]], age[ii]);
                    cnt[match->cur[j]] ++;
                }
                //cout << cnt[match->cur] << " : " << s[match->cur] << endl;
            }
            match = match->fail;
        }
    }
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
    memset(age, 0, sizeof(age));
    memset(mx, -1, sizeof(mx));
    memset(mn, 0x3f, sizeof(mn));
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i < n; ++ i)s[i].clear();
}

int main(){
    ios::sync_with_stdio(false);
    cin >> n;
    init();
    for(int i = 0; i < n; ++ i){
        cin >> s[i] >> age[i];
        insert(i);
    }
    Get_fail();
    for(int i = 0; i < n; ++ i)
        ACA(i);
    for(int i = 0; i < n; ++ i)
        cout << cnt[i] << ' ' << mn[i] << ' ' << mx[i] << endl;
    return 0;
}

/**

5
aaaaaaa 100
bcgfhj 20
aa 45
bacbacbacbac 66
bacbacbacbac 6

*/