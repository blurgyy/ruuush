#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int T;
char scr[30][30];

void init()
{
    memset(scr, 0, sizeof(scr));
}

int check(int col)
{
    if(scr[1][col+1] == 'X' && scr[2][col] == 'X' && scr[2][col+3] == 'X' && scr[4][col+1] == '.' && scr[6][col] == 'X' && scr[6][col+3] == 'X' && scr[7][col+1] == 'X')return 0;
    if(scr[1][col+1] == '.' && scr[2][col] == '.' && scr[2][col+3] == 'X' && scr[4][col+1] == '.' && scr[6][col] == '.' && scr[6][col+3] == 'X' && scr[7][col+1] == '.')return 1;
    if(scr[1][col+1] == 'X' && scr[2][col] == '.' && scr[2][col+3] == 'X' && scr[4][col+1] == 'X' && scr[6][col] == 'X' && scr[6][col+3] == '.' && scr[7][col+1] == 'X')return 2;
    if(scr[1][col+1] == 'X' && scr[2][col] == '.' && scr[2][col+3] == 'X' && scr[4][col+1] == 'X' && scr[6][col] == '.' && scr[6][col+3] == 'X' && scr[7][col+1] == 'X')return 3;
    if(scr[1][col+1] == '.' && scr[2][col] == 'X' && scr[2][col+3] == 'X' && scr[4][col+1] == 'X' && scr[6][col] == '.' && scr[6][col+3] == 'X' && scr[7][col+1] == '.')return 4;
    if(scr[1][col+1] == 'X' && scr[2][col] == 'X' && scr[2][col+3] == '.' && scr[4][col+1] == 'X' && scr[6][col] == '.' && scr[6][col+3] == 'X' && scr[7][col+1] == 'X')return 5;
    if(scr[1][col+1] == 'X' && scr[2][col] == 'X' && scr[2][col+3] == '.' && scr[4][col+1] == 'X' && scr[6][col] == 'X' && scr[6][col+3] == 'X' && scr[7][col+1] == 'X')return 6;
    if(scr[1][col+1] == 'X' && scr[2][col] == '.' && scr[2][col+3] == 'X' && scr[4][col+1] == '.' && scr[6][col] == '.' && scr[6][col+3] == 'X' && scr[7][col+1] == '.')return 7;
    if(scr[1][col+1] == 'X' && scr[2][col] == 'X' && scr[2][col+3] == 'X' && scr[4][col+1] == 'X' && scr[6][col] == 'X' && scr[6][col+3] == 'X' && scr[7][col+1] == 'X')return 8;
    if(scr[1][col+1] == 'X' && scr[2][col] == 'X' && scr[2][col+3] == 'X' && scr[4][col+1] == 'X' && scr[6][col] == '.' && scr[6][col+3] == 'X' && scr[7][col+1] == 'X')return 9;
}

int main()
{
    scanf("%d\n", &T);
    while(T--)
    {
        init();
        for(int i = 1; i <= 7; i++)
            scanf("%s", scr[i] + 1);
        printf("%d%d:%d%d\n", check(1), check(6), check(13), check(18));
    }
    return 0;
}


/**

1
.XX...XX.....XX...XX.
X..X....X......X.X..X
X..X....X.X....X.X..X
......XX.....XX...XX.
X..X.X....X....X.X..X
X..X.X.........X.X..X
.XX...XX.....XX...XX.

*/
