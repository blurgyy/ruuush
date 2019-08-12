#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n;
bool rooms[20];
char s[maxn];

int leftmost(){
    for(int i = 0; i < 10; ++ i){
        if(rooms[i] == false){
            rooms[i] = true;
            return i;
        }
    }
}

int rightmost(){
    for(int i = 9; i >= 0; -- i){
        if(rooms[i] == false){
            rooms[i] = true;
            return i;
        }
    }
}

int main(){
    while(~scanf("%d%s", &n, s)){
        memset(rooms, false, sizeof(rooms));
        for(int i = 0; i < n; ++ i){
            if(s[i] == 'L'){
                leftmost();
            }
            else if(s[i] == 'R'){
                rightmost();
            }
            else if(s[i] >= '0' && s[i] <= '9'){
                rooms[s[i]-'0'] = false;
            }
            else {
                printf("wtf\n");
            }
        }
        for(int i = 0; i < 10; ++ i){
            printf("%d", rooms[i]);
        }
        printf("\n");
    }
    return 0;
}
