#include<cstdio>
#include<map>
using namespace std;

int a, b;
bool ans;
map<int, int> tree;

void init()
{
    tree.clear();
    ans = true;
}

void out()
{
    if(ans)printf("yes\n");
    else printf("no\n");
}

int main()
{
    init();
    while(~scanf("%d%d", &a, &b) && (a != -1 && b != -1))
    {
        if(a == 0 && b == 0)
        {
            out();
            init();
            continue;
        }
        if(tree[b] && ans)ans = false;
        else if(tree[b] == 0)tree[b] = a;
    }
}
