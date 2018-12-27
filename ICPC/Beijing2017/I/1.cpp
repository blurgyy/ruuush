#include<bits/stdc++.h>
using namespace std;
const int maxn = 131080;

struct Segtree
{
    int left, right;
    int mi[2], ma[2];
}Tree[maxn<<2];
int T;
int k, len, a[maxn], Len[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072};
int op;

void PushUp(int index){
    Tree[nowNode].mi[0] = 
}

void Build(int nowNode, int left, int right){
    Tree[nowNode].mi[0] = Tree[nowNode].mi[1] = Tree[nowNode].ma[0] = Tree[nowNode].ma[1] = 0;
    if(left == right){
        Tree[nowNode].mi[0] = Tree[nowNode].mi[1] = Tree[nowNode].ma[0] = Tree[nowNode].ma[1] = a[right];
    }
    int mid = (left + right)>>1;
    Build(nowNode<<1, left, mid);
    Build(nowNode<<1|1, mid + 1, right);
    PushUp(nowNode);
}

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d", &k);
        len = Len[k];
        for(int i = 0; i < len; ++ i)
            scanf("%d", a + i);
        Build(1, 1, len);

    }
    return 0;
}

/**
2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072
*/