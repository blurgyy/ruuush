### williamking5

*****

###### time limit: 1000ms

williamking5 热爱数学。

他想知道数学的终极问题，$A + B$ 等于多少



**Input**

第一行为一个正整数 $T(T \leq 10)$，表示测试样例的数目。

对于每个测试样例：

第一行为空格隔开的两个数 $A, B(1 \leq A,B\leq 10^{12})$，含义见题目描述。



**Output**

对于每个测试样例：

输出 $A + B$ 的结果



**Example Input**

```
3
1 2
2 3
12345678987 12345678987
```



**Example Output**

```
3
5
24691357974
```



**Hint**

- 由于题目不单调，你会发现这道题是 4 题中最简单的一个，所以请读完所有的题，不要按顺序做题

- 如果你不知道如何通过这道题，你可以看下面给的代码以及注释，有任何问题，请询问场上的常务

    ```C++
    #include <bits/stdc++.h>
    using namespace std;
    
    int main()
    {
        long long a, b;	/// 注意到数据范围超过了 int 的最大表示范围，我们应该使用 long long
        int ncase;
    
        scanf("%d", &ncase); 	/// 表示接下来会有 ncase 组问题
        while(ncase --){
            scanf("%lld%lld", &a, &b);	/// 不需要输出任何输入提示
            printf("%lld\n", a + b);	/// 请不要输出除答案以外的任何内容，别忘了输出行末换行
        }
    
        return 0;
    }
    ```

    ```java
    import java.math.BigInteger;	/// 开头的 package 要删掉
    import java.util.Scanner;
    
    public class Main {				/// 需要命名为 Main
    	static Scanner cin = new Scanner(System.in); 
    	public static void main(String[] args) {
    		BigInteger a,b;
    		while(cin.hasNext()) {
    			a = cin.nextBigInteger();
    			b = cin.nextBigInteger();
    			System.out.println(a.add(b));
    		}
    	}
    }
    /// 其余同 C++ 
    ```

- 错误示范（只要你犯了下列错误中的任意一个，你都会得到一个 Wrong Answer）

    ```C++
    #include <bits/stdc++.h>
    using namespace std;
    
    int mian()
    {
        int a, b;		/// 错误的数据类型
        int ncase;
    	
        printf("请输入测试组数：");	/// 没必要的文字提示
        scanf("%d", &ncase);
        while(ncase --){
            printf("请输入 A 和 B：");	/// 没必要的文字提示
            scanf("%lld%lld", &a, &b);
            printf("答案为：%lld", a + b);	/// 没必要的文字提示，同时还忘了换行
        }
    
        return 0;
    }
    ```










