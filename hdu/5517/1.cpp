#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pii> pipii;
const int maxn = 100010;

int T, n, m;
int ctot;
int cnta[maxn];
pii A[maxn];        ///(b, a)
pipii B[maxn];      ///(e, c, d)
pipii C[maxn<<2];   ///(a, c, d)

void print(pii a[], int tot, int start = 1){
    for(int i = start; i <= tot; ++ i){
        printf("(%d, %d)\n", a[i].first, a[i].second);
    }
}
void print(pipii a[], int tot, int start = 1){
    for(int i = start; i <= tot; ++ i){
        printf("(%d, (%d, %d))\n", a[i].first, a[i].second.first, a[i].second.second);
    }
}
void print(int a[], int tot, int start = 1){
    for(int i = start; i <= tot; ++ i){
        printf("%d%c", a[i], " \n"[i==tot]);
    }
}

void inpt(){
    int a, b, c, d, e;
    for(int i = 1; i <= n; ++ i){
        scanf("%d%d", &a, &b);
        A[i].first = b;
        A[i].second = a;
    }
    for(int i = 1; i <= m; ++ i){
        scanf("%d%d%d", &c, &d, &e);
        B[i].first = e;
        B[i].second.first = c;
        B[i].second.second = d;
    }
    sort(A + 1, A + 1 + n);
    sort(B + 1, B + 1 + m);
    for(int i = n, preb = A[i].first, prea = A[i].second, cnta[prea] --;; i >= 1; -- i){
        if(preb == A[i].first){
            A[i].second = prea;
            cnta[A[i].test/***/];
        }
        else {
            preb = A[i].first;
            prea = A[i].second;
        }
    }
    print(cnta, 10);
    for(int i = m, pree = B[i].first, prec = B[i].second.first, pred = B[i].second.second; i >= 1; -- i){
        if(pree == B[i].first){
            if(prec == B[i].second.first){
                B[i].second.second = pred;
            }
            else {
                prec = B[i].second.first;
                pred = B[i].second.second;
            }
        }
        else {
            pree = B[i].first;
            prec = B[i].second.first;
            pred = B[i].second.second;
        }
    }
    n = unique(A + 1, A + 1 + n) - A - 1;
    m = unique(B + 1, B + 1 + m) - B - 1;
    for(int i = 1; i <= n; ++ i){
        printf("(%d, %d)\n", A[i].second, A[i].first);
    }
    printf("\n");
    for(int i = 1; i <= m; ++ i){
        printf("(%d, %d, %d)\n", B[i].second.first, B[i].second.second, B[i].first);
    }
}

void getsetc(){
    int i = 1, j = 1;
    while(i <= n && j <= m){
        printf("i = %d, j = %d\n", i, j);
        while(A[i].first != B[j].first){
            while(i <= n && A[i].first < B[j].first){
                ++ i;
            }
            while(j <= m && B[j].first < A[i].first){
                ++ j;
            }
        }
        if(i > n || j > m){
            break;
        }
        while(A[i].first == B[j].first){
            C[++ctot] = make_pair(A[i].second, make_pair(B[i].second.first, B[i].second.second));
        }
    }
    printf("ctot = %d\n", ctot);
    print(C, ctot);
}

int main(){
    scanf("%d", &T);
    while(T --){
        for(int i = 0; i < maxn; ++ i)cnta = 1;
        scanf("%d%d", &n, &m);
        ctot = 0;
        inpt();
        getsetc();
        printf("before sort\n");
        sort(C + 1, C + 1 + ctot);
        print(C, ctot);
    }
    return 0;
}

/*
void Build(int &x, int l, int r)
{
    if(!x){
        tot ++;
        x = tot;
    }


    Build(tree[x].son[0], l, mid);
    Build(tree[x].son[1], mid + 1, r);


}*/