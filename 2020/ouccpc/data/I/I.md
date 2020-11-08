## Problem I    一天该吃几顿

$fgdgji$ 一天只吃两顿，他饿着饿着就想出了这道题

假设火星上一天有 $n$ 秒，火星人一天吃 $k$ 顿饭，吃一顿饭能使火星人 $t$ 秒不饿，食堂有时开放有时不开放

那么这个火星人至少有多少秒要饿肚子

PS：火星人是能在饱的时候去吃饭的，但是不饿的时间不叠加

PS2：如果火星人在第x秒吃饭，则在 $[x,x+t)$ 的时间段上不饿

__input:__

第一行三个整数，$n,\ k,\ t$ 

第二行 $n$ 个"0"或"1"组成的字符串，"1"表示第 $n$ 秒食堂开放，"0"表示第 $n$ 秒食堂不开放

$1 \leq t\leq n\leq 1000,0 \leq k \leq 10$ 

__Output:__

输出一个整数表示要饿肚子的时间

__Sample Input:__

```
3 3 1
111
```

__Sample Output:__

```
0
```