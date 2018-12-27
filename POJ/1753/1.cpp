#include<cstdio>
#include<string.h>
#include<algorithm>
#define maxn 100010
using namespace std;

char board[6][6];
struct cord///保存棋盘上位置的坐标的结构体
{
    int row;
    int col;
}ori[16];///棋盘上所有坐标共16个
bool as[16] = {false};///辅助数组，辅助生成所有子集

void board_init()///输入棋盘状态
{
    char c;
    int i, j;
    int p = 0;
    for(i = 1; i < 5; i++)
        scanf("%s", board[i] + 1);
    for(i = 1; i < 5; i++)
        for(j = 1; j < 5; j++)
        {
            ori[p].row = i;
            ori[p++].col = j;
        }
}

void print_board()///输出棋盘状态(just for debugging)
{
    int i, j;
    for(i = 1; i < 5; i++)
    {
        for(j = 1; j < 5; j++)
            printf("%c", board[i][j]);
        printf("\n");
    }
}

void flip(int row, int col, char ch[][6])///翻转操作
{                                           /**row行，col列，ch棋盘*/
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, -1, 0, 1};
    int i;
    for(i = 0; i < 4; i++)
    {
        int nr = row + dx[i];
        int nc = col + dy[i];
        if(ch[nr][nc] == 'b')ch[nr][nc] = 'w';
        else ch[nr][nc] = 'b';
    }
    if(ch[row][col] == 'b')ch[row][col] = 'w';
    else ch[row][col] = 'b';
}

bool check(char ch[][6])///检查棋盘是否已达到全为一色的状态
{                       /**ch为要被检查的棋盘*/
    int i, j;
    char tmp = ch[1][1];
    for(i = 1; i <= 4; i++)
        for(j = 1; j <= 4; j++)
            if(ch[i][j] != tmp)return false;
    return true;
}

void init(char ch[][6])///保留原始棋盘，复制出来一个棋盘用于后面改变
{                       /**ch为被复制出的棋盘*/
    int i, j;
    for(i = 1; i < 5; i++)
        for(j = 1; j < 5; j++)
        ch[i][j] = board[i][j];
}

bool Find(int num, char ch[][6])///生成所有子集并检查是否能达到要求
{                               /**num为要生成的子集的长度， ch为用于检查的棋盘*/
    int i;
    for(i = 0; i < num; i++)
        as[i] = true;
    do
    {
        init(ch);           ///每次都要初始化棋盘
        for(i = 0; i < 16; i++)
            if(as[i]) flip(ori[i].row, ori[i].col, ch);
        if(check(ch))return true;///有任何一次得到了全为一色直接return true
    }
    while(prev_permutation(as, as + 16));///prev_permutation函数返回值类型为bool，不能再做出改变时返回false
    return false;///从未return true 就false
}

int main()
{
    int ans = 1000;///ans初始化为1000
    int i, j;
    board_init();///输入棋盘
    char ch[6][6];
    for(i = 0; i < 16; i++)///0步到15步全判断
        if(Find(i, ch))ans = min(ans, i);///每次仅保留最小的步数
    if(ans == 1000)printf("Impossible\n");///ans值未改变过则Impossible
    else printf("%d\n", ans);
    return 0;
}
