#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define maxn 100010
using namespace std;

struct node
{
    int index;
    vector<int> edge;
}Tree[maxn];

node *pa[maxn];

void init()
{

}

int main()
{
    for(int i = 0; i < maxn; i++)
        Tree[i].index = i;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &k);
        int tmp;
        for(int i = 2; i <= k; i++)
        {
            scanf("%d", &tmp);
            Tree[i].edge.push_back(tmp);
            Tree[tmp].edge.push_back(i);

        }
    }
}
