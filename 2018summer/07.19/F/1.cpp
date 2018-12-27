#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;
const int fib[46] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296, 433494437, 701408733, 1134903170, 1836311903};

int n;
struct Node{
    int id, val;
    bool operator<(Node a){
        return val < a.val;
    }
}a[maxn];

int bs(int e, Node arr[], int left = 0, int right = 45){
    //printf("%d %d\n", left, right);
    if(left >= right)return right;
    int mid = left + right >> 1;
    if(e <= arr[mid].val)return bs(e, arr, left, mid);
    return bs(e, arr, mid + 1, right);
}

int main(){

    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++ i){
            scanf("%d", &a[i].val);
            a[i].id = i;
        }
        sort(a, a + n);
        if(a[0].val == a[1].val && a[1].val == 1){
            printf("1 2\n");
            continue;
        }
        int aa = -1, bb = -1;
        for(int i = 1; i < 46; ++ i){
            if(a[bs(fib[i], a, 1, n-1)].val == fib[i] && a[bs(fib[i-1], a, 1, n-1)].val == fib[i-1]){
                aa = a[bs(fib[i-1], a, 1, n-1)].id + 1;
                bb = a[bs(fib[i], a, 1, n-1)].id + 1;
                break;
            }
        }
        if(aa == -1){
            printf("impossible\n");
        }
        else {
            printf("%d %d\n", aa, bb);
        }
    }
    return 0;
}