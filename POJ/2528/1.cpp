#include<cstdio>
#include<cstring>
#include<map>
#include<set>
#include<algorithm>
//#define maxn 50010
//#define INF 2147483647
#define ll long long
using namespace std;
const int maxn = 50010;
const int INF = 0x7fffffff;///max int
int T, n;
int p = 1;
struct segTree
{
    int left, right;
    int current;
    set<int> cnt;
    void update(int post_index)
    {

    }
}Tree[4*maxn];
struct cord
{
    int left;
    int right;
}interval[maxn];
map<int, int> Disc;

void PushUp(int index)
{
    int left = index<<1, right = index<<1|1;
    Tree[index].cnt.clear();
    set<int>::iterator i;
    for(i = Tree[left].cnt.begin(); i != Tree[left].cnt.end(); ++i)
        Tree[index].cnt.insert(*i);
    for(i = Tree[right].cnt.begin(); i != Tree[right].cnt.end(); ++i)
        Tree[index].cnt.insert(*i);
}

void Build(int nowNode, int left, int right)
{
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].current = -1;
    Tree[nowNode].cnt.clear();
    if(left == right)return;
    int mid = (left + right)>>1;
    Build(nowNode<<1, left, mid);
    Build(nowNode<<1|1, mid+1, right);
    PushUp(nowNode);
}

void Update(int nowNode, int uleft, int uright, int post_index)
{
    int left = Tree[nowNode].left;
    int right = Tree[nowNode].right;
    if(left == right)
    {
        Tree[nowNode].cnt.clear();
        Tree[nowNode].cnt.insert(post_index);
    }
    if(uleft <= left && right <= uright)
    {
        Tree[nowNode].cnt.insert(post_index);
        return;
    }
    int mid = (left + right)>>1;
    if(uleft <= mid)Update(nowNode<<1, uleft, uright, post_index);
    if(uright > mid)Update(nowNode<<1|1, uleft, uright, post_index);
    PushUp(nowNode);
    //printf("%d to %d: ", left, right), out(nowNode);
}

void init()
{
    p = 0;
    Disc.clear();
}

int main()
{
    scanf("%d", &T);
    while(T--)
    {
        init();
        int a, b;
        scanf("%d", &n);
        for(int i = 0; i < n; ++i)
        {
            scanf("%d%d", &interval[i].left, &interval[i].right);
            Disc[interval[i].left] = INF;
            Disc[interval[i].right] = INF;
        }
        for(map<int, int>::iterator i = Disc.begin(); i != Disc.end(); ++i)
            i->second = ++p;
        Build(1, 1, p);
        for(int i = 0; i < n; i++)
        {
            //printf("%d %d:\n", Disc[interval[i].left], Disc[interval[i].right]);
            Update(1, Disc[interval[i].left], Disc[interval[i].right], i+1);
            //printf("\n");
        }
        /*for(int i = 1; i <= 15; i++)
            printf("%d, %d to %d: ", i, Tree[i].left, Tree[i].right), out(i);*/
        printf("%d\n", Tree[1].cnt.size());
    }
    return 0;
}
/**

1
5
1 4
2 6
8 10
3 4
7 10

*/
