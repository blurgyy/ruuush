#include<stdio.h>
#include<string.h>
#include<malloc.h>

char handle[4][4];  //存储字符
int record[4][4];   //记录每一位操作次数

bool set_handle()
{
    int i, j;
    for(i = 0; i < 4; i++)
    {
        scanf("%s", handle[i]);
    }
    memset(record, 0, sizeof(record));
    return true;
}

char change_state(char state)
{
    if(state == '+')
        return '-';
    return '+';
}

//把m行n列的开关按下
void flip(int m, int n)
{
    int i, j;
    for(j = 0; j < 4; j++)  //行操作
    {
        handle[m][j] = change_state(handle[m][j]);
    }
    for(i = 0; i < 4; i++)  //列操作
    {
        if(i != m)
          handle[i][n] = change_state(handle[i][n]);
    }
    record[m][n]++; //执行一次操作
}

//对数组中所有+位置的行和列所有的开关执行一次flip操作
void full_flip()
{
    int i, j;
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            if(handle[i][j] == '+')
            {
                int t;
                for(t = 0; t < 4; t++)
                {
                    flip(i, t);
                }

                for(t = 0; t < 4; t++)
                {
                    if(t != i)
                    {
                       flip(t,j);
                    }

                }
            }
        }
    }
}


//遍历record数组，统计操作次数
void solute()
{
    int count = 0;
    int i, j;
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            if(record[i][j] & 1  != 0)
            {
                count ++;
            }
        }
    }
    printf("%d\n", count);
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            if(record[i][j] & 1  != 0)
            {
                printf("%d %d\n", i+1, j+1);
            }
        }
    }

}

int main(void)
{
    while(set_handle())
    {
        full_flip();
        solute();
    }
    return 0;
}
