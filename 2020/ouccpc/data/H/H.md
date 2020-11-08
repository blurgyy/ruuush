## Problem H     Bushiczl

从某一届开始，ACM社团总有以Bushixxx命名的人

现在你拿到了QQ群里一些人的id，你要写程序分析这些id是不是Bushixxx格式的

我们判断一个id是不是Bushixxx格式，当且仅当：去掉非字母非数字的字符后，剩下的字符内，字母部分是连续的"Bushi"加上一串字母，不区分大小写

合法格式例如：
Bushiczl
bushiczlnb
BushiBushi
---123b.U.s.H.i.q-45-

非法格式例如：
bBushiczl    字母部分不是Bushixxx格式，前面多了个b
bushic5zl    字母部分不连续
-0-bushi-0-  bushi后面没有其他字母

__Input:__

第一行一个字符串 $s$

$1\leq len(s)\leq50$

__Output:__

对于每一个测试数据，合法输出 "Yes"，非法输出"No"

__Sample Input:__

```
bBushiczl
```

__Sample Output:__

```
No
```
