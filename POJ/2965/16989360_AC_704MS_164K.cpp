#include<cstdio>
#include<algorithm>
using namespace std;

bool handle[6][6] = {false};

struct cord
{
    int row;
    int col;
}all[16], result[20];
int ptr = 0;

void output(bool mat[][6])
{
    int i, j;
    for(i = 1; i < 5; i++)
    {
        for(j = 1; j < 5; j++)
            printf("%d", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

void change(int row, int col, bool temp[][6])
{
    int i, j;
    for(i = 1; i < 5; i++)
        temp[i][col] = !temp[i][col];
    for(j = 1; j < 5; j++)
        temp[row][j] = !temp[row][j];
    temp[row][col] = !temp[row][col];
}

bool input()
{
    int i, j;
    char tmp[6][6];
    for(i = 1; i < 5; i++)
        scanf("%s", tmp[i] + 1);
    for(i = 1; i < 5; i++)
        for(j = 1; j < 5; j++)
        handle[i][j] = (tmp[i][j] == '-');
    return true;
}

void init(bool temp[][6])
{
    int i, j;
    for(i = 1; i < 5; i++)
        for(j = 0; j < 5; j++)
        temp[i][j] = handle[i][j];
}

bool check(bool temp[][6])
{
    int i, j;
    for(i = 1; i < 5; i++)
        for(j = 1; j < 5; j++)
        if(temp[i][j] == 0)return false;
    return true;
}

bool Find(bool temp[][6], int len_sub)
{
    int i, j;
    bool assist[16] = {false};
    for(i = 0; i < len_sub; i++)
        assist[i] = true;
    do
    {
        init(temp);
        ptr = 0;
        for(i = 0; i < 16; i++)
            if(assist[i])
            {
                change(all[i].row, all[i].col, temp);
                result[ptr].row = all[i].row;
                result[ptr++].col = all[i].col;
            }
        if(check(temp))return true;
    }
    while(prev_permutation(assist, assist + 16));
    return false;
}

int main()
{
    int i, j, p = 0;
    int ans = 1000;
    bool temp[6][6];
    for(i = 1; i <= 4; i++)
        for(j = 1; j <= 4; j++)
        {
            all[p].row = i;
            all[p++].col = j;
        }
    input();
    for(i = 0; i <= 16; i++)
        if(Find(temp, i))
        {
            ans = i;
            break;
        }
    printf("%d\n", ans);
    for(i = 0; i < ptr; i++)
        printf("%d %d\n", result[i].row, result[i].col);
    return 0;
}
