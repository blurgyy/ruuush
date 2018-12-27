#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <bitset>
#include <map>
#include <vector>
#include <stack>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <ctime>
#include <assert.h>
#ifdef LOCAL
#define debug(x) cout<<#x<<" = "<<(x)<<endl;
#else
#define debug(x) 1;
#endif
 
#define chmax(x,y) x=max(x,y)
#define chmin(x,y) x=min(x,y)
#define lson id<<1,l,mid
#define rson id<<1|1,mid+1,r
#define lowbit(x) x&-x
#define mp make_pair
#define pb push_back
#define fir first
#define sec second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
 
const int MOD = 998244353;
const double PI = acos (-1.);
const double eps = 1e-10;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 2e5 + 5;
 
char s[MAXN];
 
const int maxn = 4e5 + 100;
 
struct SAM
{
    // ch 转移函数, pre父亲, len最长长度, tag前缀标记, in入度, endnum endpos的个数 o 顺序
    int ch[maxn][26],pre[maxn],len[maxn],tag[maxn],in[maxn],endnum[maxn], cnt[maxn];
    ll cnt2[maxn];
    int last, tot;
    void init(){
        last = tot = 0;
        memset(ch[0], -1, sizeof ch[0]);
        pre[0] = -1; len[0] = in[0] = 0;
        memset(cnt, 0, sizeof(cnt));
        memset(cnt2, 0, sizeof(cnt2));
    }
    // 加多个串时为了保证不跨串算
    void reset() {last = 0;}
 
    int extend(int c, int ind){
        int p = last, np = ++tot;
        len[np] = len[p] + 1; tag[np] = ind;
        memset(ch[np], -1, sizeof ch[np]);
        in[np] = 0;
        while(~p && ch[p][c] == -1) ch[p][c] = np, p = pre[p];
        if(p == -1) {
            pre[np] = 0;
            in[0]++;
        }
        else{
            int q = ch[p][c];
            if(len[q] != len[p] + 1){
                int nq = ++tot;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                in[nq] = tag[nq] = 0;
                len[nq] = len[p] + 1;
                pre[nq] = pre[q];
                pre[q] = pre[np] = nq;
                in[nq] += 2;
                while(~p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
            }
            else {
                pre[np] = q;
                in[q]++;
            }
        }
        last = np;
        return len[np] - len[pre[np]];
    }
 
    // 按照pre树计数排序  who为第i个位置的编号
    int who[maxn], a[maxn];
    void Sort() {
    	for(int i = 1; i <= tot; i++) a[i] = 0;
        for(int i = 1; i <= tot; i++) a[len[i]]++;
        for(int i = 1; i <= tot; i++) a[i] += a[i - 1];
        for(int i = 1; i <= tot; i++) who[a[len[i]]--] = i;
 
        /*下面是求endnum，不用可以注释掉*/
        for(int i = 1; i <= tot; i++) endnum[i] = 0;
        for(int i = tot; i >= 1; i--) {
            int u = who[i];
            if(tag[u]) endnum[u]++;
            endnum[pre[u]] += endnum[u];
        }
    }
 
 
 
 
}sam;
 
const int N = 26 ;
 
struct Palindromic_Tree {
    int nxt[MAXN][N] ;//next指针，next指针和字典树类似，指向的串为当前串两端加上同一个字符构成
    int fail[MAXN] ;//fail指针，失配后跳转到fail指针指向的节点
    int cnt[MAXN] ; //i表示的回文串在原串出现多少次（建树时求出的不是完全的，最后count()函数跑一遍以后才是正确的）
    int num[MAXN] ; //表示以节点i表示的最长回文串的最右端点为回文串结尾的回文串个数
    int len[MAXN] ;//len[i]表示节点i表示的回文串的长度（一个节点表示一个回文串）
    int S[MAXN] ;//存放添加的字符
    int last ;//指向新添加一个字母后所形成的最长回文串表示的节点。
    int n ;//表示添加的字符个数。
    int p ;//表示添加的节点个数。
 
    int newnode ( int l ) {//新建节点
        for ( int i = 0 ; i < N ; ++ i ) nxt[p][i] = 0 ;
        cnt[p] = 0 ;
        num[p] = 0 ;
        len[p] = l ;
        return p ++ ;
    }
 
    void init () {//初始化
        p = 0 ;
        newnode (  0 ) ;
        newnode ( -1 ) ;
        last = 0 ;
        n = 0 ;
        S[n] = -1 ;//开头放一个字符集中没有的字符，减少特判
        fail[0] = 1 ;
    }
 
    int get_fail ( int x ) {//和KMP一样，失配后找一个尽量最长的
        while ( S[n - len[x] - 1] != S[n] ) x = fail[x] ;
        return x ;
    }
 
    int add ( int c ) {
        S[++ n] = c ;
        int cur = get_fail ( last ) ;//通过上一个回文串找这个回文串的匹配位置
        if ( !nxt[cur][c] ) {//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            int now = newnode ( len[cur] + 2 ) ;//新建节点
            fail[now] = nxt[get_fail ( fail[cur] )][c] ;//和AC自动机一样建立fail指针，以便失配后跳转
            nxt[cur][c] = now ;
            num[now] = num[fail[now]] + 1 ;
        }
        last = nxt[cur][c] ;
        cnt[last] ++ ;
        return num[last];
    }
 
    void count () {
        for ( int i = p - 1 ; i >= 0 ; -- i ) cnt[fail[i]] += cnt[i] ;
        //父亲累加儿子的cnt，因为如果fail[v]=u，则u一定是v的子回文串！
    }
} pam;
 
ll ans1, ans2;
int pa[MAXN];
 
 
void solve(char * s, int n) {
    sam.init(); pam.init();
    for (int i = 1; i <= n; i++) sam.extend(s[i] - 'a', i);
    sam.Sort();
    for (int i = 1; i <= n; i++) pa[i] = pam.add(s[i] - 'a');
    int now = 0, mylen = 0;
    printf("sssssssssssssssss = %s\n", s + 1);
    printf("1 ans = %lld, ans2 = %lld\n", ans1, ans2);
    for (int i = n; i >= 1; i--) {
        printf("matching %c\n", s[i]);
        int id = s[i] - 'a';
        while(now && sam.ch[now][id] == -1) {
            now = sam.pre[now];
            mylen = sam.len[now];
        }
        if (sam.ch[now][id] != -1) {
            mylen++;
            now = sam.ch[now][id];
            int add = sam.endnum[now] * (mylen - sam.len[sam.pre[now]]);
            printf("add = %d, mul = %d\n", add, pa[i-1]);
            ans1 += sam.endnum[now] * (mylen - sam.len[sam.pre[now]]);
            ans2 += (ll) sam.endnum[now] * (mylen - sam.len[sam.pre[now]]) * pa[i - 1];
            sam.cnt[sam.pre[now]]++;
            sam.cnt2[sam.pre[now]] += pa[i - 1];
        }
    }
    printf("2 ans = %lld, ans2 = %lld\n", ans1, ans2);
 
    for (int i = sam.tot; i >= 1; i--) {
        int u = sam.who[i];
        ans1 += (ll)sam.cnt[u] * sam.endnum[u] * (sam.len[u] - sam.len[sam.pre[u]]);
        ans2 += (ll)sam.cnt2[u] * sam.endnum[u] * (sam.len[u] - sam.len[sam.pre[u]]);
        sam.cnt[sam.pre[u]] += sam.cnt[u];
        sam.cnt2[sam.pre[u]] += sam.cnt2[u];
    }
    printf("3 ans = %lld, ans2 = %lld\n", ans1, ans2);
}
 
void Print(ll x) {
    vector<int> v;
    do {
        v.pb(x % 10);
        x /= 10;
    } while(x);
    reverse(v.begin(), v.end());
    for (int i : v) printf("%d", i);
}
 
int main() {
#ifdef LOCAL
    freopen ("input.txt", "r", stdin);
#endif
    int n;
    scanf ("%d %s", &n, s + 1);
    solve(s, n);
    reverse(s + 1, s + 1 + n);
    solve(s, n);
    Print(ans1 / 2 + ans2);
    puts("");
    //system("pause");
    return 0;
}
