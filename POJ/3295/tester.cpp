#include<cstdio>
#include<cstdlib>
#include<time.h>
using namespace std;

int main(){
    srand(time(NULL));
    char op[5] = {'K', 'A', 'N', 'C', 'E'};
    char ab[5] = {'p', 'q', 'r', 's', 't'};
    int time = 80;
    while(time--){
        int t = rand() % 60 + 1;
        while(t--){
            int out = rand()%5;
            printf("%c", op[out]);
            if(out == 0) printf("%c%c", ab[rand()%5], ab[rand()%5]);
            else if(out == 1) printf("%c%c", ab[rand()%5], ab[rand()%5]);
            else if(out == 2) printf("%c", ab[rand()%5]);
            else if(out == 3)  printf("%c%c", ab[rand()%5], ab[rand()%5]);
            else printf("%c%c", ab[rand()%5], ab[rand()%5]);
        }
        printf("\n");
    }
    return 0;
}
