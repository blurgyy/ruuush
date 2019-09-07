#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

int n;
int a[maxn], b[maxn];
int heap[maxn];

int is_ins(){
    int pos = 1;
    for(int i = 1; i < n; ++ i){
        if(b[i+1] < b[i]){
            pos = i + 1;
            break;
        }
    }
    for(int i = pos; i <= n; ++ i){
        if(a[i] != b[i]) return -1;
    }
    return pos;
}

void insert(int pos){
    int x = b[pos];
    for(int i = 1; i < pos; ++ i){
        if(i == 1 && x < b[i]){
            for(int j = pos; j > i; -- j){
                b[j] = b[j-1];
            }
            b[i] = x;
            return;
        }
        else if(i == pos-1 && x > b[i]){
            printf("wtf\n");
            return;
        }
        else if(b[i-1] < x && b[i] > x){
            for(int j = pos; j > i; -- j){
                b[j] = b[j-1];
            }
            b[i] = x;
            return;
        }
    }
}

int build(int heap[]){
    heap[1] = b[1];
    for(int i = 2; i <= n; ++ i){
        if(b[i] < heap[i>>1]){
            heap[i] = b[i];
        }
        else {
            return i-1;
        }
    }
}

void pop(int heap[], int rend){
    swap(heap[1], heap[rend--]);
    int now = 1;
    while(true){
        int maxx = -1;
        int maxpos = -1;
        if((now<<1) <= rend && maxx < heap[now<<1]){
            maxx = heap[now<<1];
            maxpos = now<<1;
        }
        if((now<<1|1) <= rend && maxx < heap[now<<1|1]){
            maxx = heap[now<<1|1];
            maxpos = now<<1|1;
        }
        if(maxpos == -1){
            break;
        }
        swap(heap[now], heap[maxpos]);
        now = maxpos;
        // if((now<<1) <= rend && heap[now] < heap[now<<1]){
        //     swap(heap[now], heap[now<<1]);
        //     if((now<<1|1) <= rend && heap[now] < heap[now<<1|1]){
        //         swap(heap[now], heap[now<<1|1]);
        //     }
        //     nxt = now << 1;
        // }
        // if((now<<1|1) <= rend && heap[now] < heap[now<<1|1]){
        //     swap(heap[now], heap[now<<1|1]);
        //     if((now<<1) <= rend && heap[now] < heap[now<<1]){
        //         swap(heap[now], heap[now<<1]);
        //     }
        //     nxt = now << 1 | 1;
        // }
    }
}

int main(){
    while(~scanf("%d", &n)){
        for(int i = 1; i <= n; ++ i) scanf("%d", a + i);
        for(int i = 1; i <= n; ++ i) scanf("%d", b + i);
        int pos = is_ins();
        if(pos != -1){
            insert(pos);
            printf("Insertion Sort\n");
            for(int i = 1; i <= n; ++ i){
                printf("%d%c", b[i], " \n"[i==n]);
            }
        }
        else {
            pos = build(heap);
            pop(b, pos);
            printf("Heap Sort\n");
            for(int i = 1; i <= n; ++ i){
                printf("%d%c", b[i], " \n"[i==n]);
            }
        }
    }
    return 0;
}
