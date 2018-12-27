#include <bits/stdc++.h>
#define ws wss
#define rank rk
typedef long long ll;
using namespace std;
const int N = 200010;
const int inf = 0x3f3f3f3f;

int A, B;
char s[N];

int cmp(int *r,int a,int b,int l)
{
    return (r[a]==r[b]) && (r[a+l]==r[b+l]);
}
int wa[N],wb[N],ws[N],wv[N];
int rank[N],height[N];
void DA(int *r,int *sa,int n,int m)  //此处N比输入的N要多1，为人工添加的一个字符，用于避免CMP时越界
{
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0; i<m; i++) ws[i]=0;
    for(i=0; i<n; i++) ws[x[i]=r[i]]++;
    for(i=1; i<m; i++) ws[i]+=ws[i-1];
    for(i=n-1; i>=0; i--) sa[--ws[x[i]]]=i; //预处理长度为1
    for(j=1,p=1; p<n; j*=2,m=p) //通过已经求出的长度J的SA，来求2*J的SA
    {
        for(p=0,i=n-j; i<n; i++) y[p++]=i; // 特殊处理没有第二关键字的
        for(i=0; i<n; i++) if(sa[i]>=j) y[p++]=sa[i]-j; //利用长度J的，按第二关键字排序
        for(i=0; i<n; i++) wv[i]=x[y[i]];
        for(i=0; i<m; i++) ws[i]=0;
        for(i=0; i<n; i++) ws[wv[i]]++;
        for(i=1; i<m; i++) ws[i]+=ws[i-1];
        for(i=n-1; i>=0; i--) sa[--ws[wv[i]]]=y[i]; //基数排序部分
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1; i<n; i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;  //更新名次数组x[],注意判定相同的
    }
}
 
void calheight(int *r,int *sa,int n)  // 此处N为实际长度
{
    /**/memset(height, 0, sizeof(height));
    int i,j,k=0;        // height[]的合法范围为 1-N, 其中0是结尾加入的字符
    for(i=1; i<=n; i++) rank[sa[i]]=i; // 根据SA求RANK
    for(i=0; i<n; height[rank[i++]] = k ) // 定义：h[i] = height[ rank[i] ]
        for(k?k--:0,j=sa[rank[i]-1]; r[i+k]==r[j+k]; k++); //根据 h[i] >= h[i-1]-1 来优化计算height过程
}

int aa[N];
int sa[N];
ll cnt[N];
int l[N], r[N];

struct STACK{
    int actfstk[N];
    int sz;
    STACK(){init();}
    void init(){sz = 0; memset(actfstk, 0, sizeof(actfstk));}
    void push(int x){actfstk[sz++] = x;}
    void pop(){sz --;}
    int top(){return actfstk[sz-1];}
    int size(){return sz;}
    bool empty(){return sz == 0;}
}stk;

struct stn{
    int left, right;
    int maxv, minv;
}Tree[N<<2];
void pushUp(int now){
    Tree[now].maxv = max(Tree[now<<1].maxv, Tree[now<<1|1].maxv);
    Tree[now].minv = min(Tree[now<<1].minv, Tree[now<<1|1].minv);
}
void build(int arr[], int left, int right, int now = 1){
    Tree[now].left = left;
    Tree[now].right = right;
    if(left == right){
        Tree[now].maxv = arr[right];
        Tree[now].minv = arr[right];
        return;
    }
    int mid = left + right >> 1;
    build(arr, left, mid, now << 1);
    build(arr, mid + 1, right, now << 1 | 1);
    pushUp(now);
}
void update(int pos, int after, int now = 1){
    int left = Tree[now].left, right = Tree[now].right;
    if(left == right){
        Tree[now].maxv = after;
        Tree[now].minv = after;
        return;
    }
    int mid = left + right >> 1;
    if(pos <= mid)update(pos, after, now << 1);
    else update(pos, after, now << 1 | 1);
    pushUp(now);
}
int querymax(int qleft, int qright, int now = 1){
    int left = Tree[now].left, right = Tree[now].right;
    if(qleft <= left && right <= qright){
        return Tree[now].maxv;
    }
    int ret = -inf;
    int mid = left + right >> 1;
    if(qleft <= mid)ret = max(ret, querymax(qleft, qright, now << 1));
    if(qright > mid)ret = max(ret, querymax(qleft, qright, now << 1 | 1));
    return ret;
}
int querymin(int qleft, int qright, int now = 1){
    //printf("left = %d, right = %d\n", qleft, qright);
    int left = Tree[now].left, right = Tree[now].right;
    if(qleft <= left && right <= qright){
        return Tree[now].minv;
    }
    int ret = inf;
    int mid = left + right >> 1;
    if(qleft <= mid)ret = min(ret, querymin(qleft, qright, now << 1));
    if(qright > mid)ret = min(ret, querymin(qleft, qright, now << 1 | 1));
    return ret;
}
int subvmax(int pos, int left, int right){
    int tmp = querymax(pos, pos);
    update(pos, 0);
    int ret = querymax(left, right);
    update(pos, tmp);
    return ret;
}
int subvmin(int pos, int left, int right){
    int tmp = querymin(pos, pos);
    update(pos, 0);
    int ret = querymin(left, right);
    update(pos, tmp);
    return ret;
}

int main(){
    while(~scanf("%s%d%d", s, &A, &B)){
        //printf("%d %d\n", A, B);
        int len = strlen(s);
        while(len > N);
        //printf("len = %d\n", len);
        for(int i = 0; i < len; ++ i){
            aa[i] = s[i];
        }
        aa[len] = 0;
        DA(aa, sa, len+1, 256);
        calheight(aa, sa, len);
        build(height, 1, len + 1);

        stk.init();
        stk.push(1);
        l[1] = 1;
        int tmp = len + 1;
        for(int i = 2; i <= tmp; ++ i){
            if(height[i] != 0){
                while(height[stk.top()] > height[i] && height[stk.top()] > 0){
                    stk.pop();
                }
                l[i] = stk.top();
            }
            else {
                l[i] = i;
            }
            stk.push(i);
        }
        stk.init();
        stk.push(tmp);

        for(int i = len; i > 0; -- i){
            if(height[i] != 0){
                while(height[stk.top()] > height[i] && height[stk.top()] > 0){
                    stk.pop();
                }
                r[i] = stk.top();
            }
            else {
                r[i] = i;
            }
            stk.push(i);
        }
        //for(int i = 1; i <= len; ++ i){
        //    printf("l[%d] = %d, ", i, l[i]);
        //    printf("r[%d] = %d\n", i, r[i]);
        //}
        memset(cnt, 0, sizeof(cnt));
        for(int i = 1; i <= len; ++ i){
            if(height[i]){
                int pos = r[i] - l[i];
                if(pos == 2){
                    cnt[pos] += height[i] - max(height[i-1], height[i+1]);
                }
                else {
                    int minx = querymin(l[i] + (height[l[i]] == 0), r[i] - (height[r[i]] == 0));
                    if(height[i] == minx){
                        cnt[pos] += height[i];
                    }
                    else {
                        cnt[pos] += height[i] - subvmin(i, l[i] + (height[l[i]] == 0), r[i] - (height[r[i]] == 0));
                    }
                }
                //printf("pos = %d\n", pos);
            }
        }
        ll x = 0;
        ll y = 0;
        for(int i = 1; i <= len; ++ i){
            x += cnt[i];
            y += len - sa[i] - height[i];
        }
        cnt[1] = y - x;
        //printf("tot = %lld\n", y);
//
        //for(int i = 1; i <= len; ++ i){
        //    printf("%s\t", s + sa[i]);
        //    printf("height[%d] = %d\n", i, height[i]);
        //}
        //for(int i = 1; i <= len; ++ i){
        //    printf("cnt[%d] = %lld\n", i, cnt[i]);
        //}

        ll ans = 0;
        for(int i = A; i <= B; ++ i){
            ans += cnt[i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}