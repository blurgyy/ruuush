#include <cstdio>

int main(){
    int g1, g2;
    while(~scanf("%d%d", &g1, &g2)){
        printf("gab[1] = %d\ngab[2] = %d\n", g1, g2);
        int nxt = g1 + g2;
        int id = 3;
        while(nxt < 1000000000){
            printf("gab[%d] = %d\n", id++, nxt);
            g1 = g2;
            g2 = nxt;
            nxt = g1 + g2;
        }
    }
    return 0;
}