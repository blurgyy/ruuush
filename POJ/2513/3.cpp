#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn = 500010;
const int prime = 1e6 + 7;
const int mod = 998244353;

vector<ll> id;
vector<pair<ll, ll> > rec;
char c1[15], c2[15];
int fa[maxn], cnt[maxn];

int idx(int x)
{
    return lower_bound(id.begin(), id.end(), x) - id.begin() + 1;
}


int Find(int x){
    return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

bool Same(int x, int y){
    return Find(x) == Find(y);
}

void Unite(int x, int y){
    int t1 = Find(x), t2 = Find(y);
    if(t1 == t2)return;
    fa[t1] = t2;
}

ll hs(char *s){
    int len = strlen(s);
    ll Hash = *s;
    for(int i = 1; i < len; ++ i)
        //Hash = (Hash * Prime + s[i-1]) % mod;
        Hash = Hash * 10 + s[i];
    return Hash;
}

void init(){
    for(int i = 0; i < maxn; ++ i)fa[i] = i;
    memset(cnt, 0, sizeof(cnt));
}

int main(){
    init();
    while(~scanf("%s%s", c1, c2)){
        ll h1 = hs(c1), h2 = hs(c2);
        printf("%lld %lld\n", h1, h2);
        id.push_back(h1);
        id.push_back(h2);
        rec.push_back(make_pair(h1, h2));
    }
    sort(id.begin(), id.end());
    for(int i = 0; i < rec.size(); ++ i){
        int id1 = idx(rec[i].first), id2 = idx(rec[i].second);
        Unite(id1, id2);
        cnt[id1] ++;
        cnt[id2] ++;
    }
    for(int i = 1; i < rec.size(); ++ i)
        printf("%d ", Find(i));
    int anc = Find(1), sz = id.size() + 1;
    bool ans = true;
    for(int i = 2; i < sz; ++ i){
        if(Find(i) != anc){
                printf("%d(Find(%d)) != %d\n", Find(i), i, anc);
                printf("(1)");
            ans = false;
            break;
        }
    }
    int odd = 0;
    for(int i = 1; i < sz; ++ i)
        odd += (cnt[i] & 1);
    if(odd != 0 && odd != 2){
        printf("(2)");
        ans = false;
    }
    if(ans)printf("Possible\n");
    else printf("Impossible\n");
    return 0;
}
