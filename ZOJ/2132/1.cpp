#include<cstdio>
#include<cstring>
const int maxn = 500100;

int n, p;
int in, stack[maxn>>1];

int main(){
    while(~scanf("%d", &n)){
        p = 0; 
        bool esc = false;
        for(int i = 0; i < n-1; ++ i){
            scanf("%d", &in);
            stack[p++] = in;
            while(p > 1 && stack[p-1] != stack[p-2])
                -- p;
            if(p > 250001){
                printf("%d\n", stack[0]);
                esc = true;
                break;
            }
        }
        if(esc)continue;
        scanf("%d", &in);
        if(n&1){
            if(p){
                printf("%d\n", stack[0]);
            }
            else{
                printf("%d\n", in);
            }
        }
        else{
            /*
            if(p){
                printf("%d\n", stack[0]);
            }
            else{
                printf("%d\n", in);
            }
            */
            printf("%d\n", stack[0]);
        }
    }
    return 0;
}