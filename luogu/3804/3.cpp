#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2000010;

struct Node{
    int to;
    int ne;
};
Node node[maxn];
int head[maxn];
int top;
void add(int from, int to){
    node[top].to = to;
    node[top].ne = head[from];
    head[from] = top;
    top ++;
}
//for(int i = head[u]; i != -1; i = node[i].ne){
//  /// 遍历
//}
void ini(){
    top = 0;
    memset(head, -1, sizeof(head));
}

#define maxn 2000010
#define sigma 26
struct SuffixAutomaton{
    int root;
    int size, last;
    int go[maxn][sigma], maxlen[maxn], par[maxn], cnt[maxn];
    bool vis[maxn];
    SuffixAutomaton(){size = 0;}
    int new_node(int len){
        memset(go[size], -1, sizeof(go[size]));
        maxlen[size] = len;
        par[size] = -1;
        return size ++;
    }
    int idx(char ch){
        return ch - 'a';
    }
    void extend(int ch){
        //printf("extending: %c\n", 'a' + ch);
        int p, q, np, nq;
        p = last;
        np = new_node(maxlen[p] + 1);
        while(p != -1 && go[p][ch] == -1){
            go[p][ch] = np;
            p = par[p];
        }
        if(p == -1){
            //printf("par[%d] = root\n", np);
            par[np] = root;
        }
        else {
            q = go[p][ch];
            if(maxlen[p] + 1 == maxlen[q]){
                par[np] = q;
            }
            else {
                nq = new_node(maxlen[p] + 1);
                memcpy(go[nq], go[q], sizeof(go[q]));
                par[nq] = par[q];
                par[q] = nq;
                par[np] = nq;
                while(p != -1 && go[p][ch] == q){
                    go[p][ch] = nq;
                    p = par[p];
                }
            }
        }
        last = np;
        cnt[np] = 1;
        //printf("cnt[%d] = %d\n", np, cnt[np]);
    }
    void init(char *s){
        size = 0;
        last = root = new_node(0);
        memset(cnt, 0, sizeof(cnt));
        int len = strlen(s);
        for(int i = 0; i < len; ++ i){
            extend(idx(s[i]));
        }
    }
}sam;
#undef sigma
#undef maxn

char s[maxn];

void count(int now = sam.root){
	for(int i = head[now]; i != -1; i = node[i].ne){
		int nxt = node[i].to;
		count(nxt);
		sam.cnt[now] += sam.cnt[nxt];
	}
}

void init(){
	ini();
	sam.init(s);
	for(int i = 0; i < sam.size; ++ i){
		add(sam.par[i], i);
	}
	count();
}

int main(){
	scanf("%s", s);
	init();
	ll ans = 0;
	for(int i = 0; i < sam.size; ++ i){
		if(sam.cnt[i] > 1){
			ans = max(ans, 1LL * sam.maxlen[i] * sam.cnt[i]);
		}
	}
	printf("%lld\n", ans);
}