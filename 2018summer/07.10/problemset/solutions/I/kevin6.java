// Solution to Interesting Integers
// Author: Kevin Buchin, based on herman.cpp

// @EXPECTED_RESULTS@: CORRECT

// If herman.cpp is the slowest we want to guarantee to pass, hopefully the corresponding java version also manages

import java.util.Scanner;

public class kevin6 {

	private static final long[] Fib = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296, 433494437, 701408733, 1134903170};
	private static int nFib = 46;
	long a_opt, b_opt;

	public kevin6(long a, long b) {
	this.a_opt = a;
	this.b_opt = b;
	}


	public void findBase(long target)
	{
		a_opt = 1; b_opt = target-1;

		for (int i = 3; Fib[i] <= target; ++i)
		{
		  long maxbmod = java.lang.Math.min(b_opt, java.lang.Math.min(Fib[i-2], (target-Fib[i-2])/Fib[i-1]));
		  for (long newbmod = 1; newbmod <= maxbmod; ++newbmod)
		  {
			long newa = (target - Fib[i-1]*newbmod) / Fib[i-2];
			if (target != Fib[i-1]*newbmod + Fib[i-2]*newa) continue;
			long newb = newbmod;
			if (newa > newb)
			{
			  newb += Fib[i-2] * (1 + (newa - newb - 1) / (Fib[i-2] + Fib[i-1]));

			  if (Fib[i-1] * newb >= target) continue;
			  newa = (target - Fib[i-1]*newb) / Fib[i-2];
			}        
			if (newb > b_opt) continue;
			if (newb == b_opt && newa >= a_opt) continue;
			a_opt = newa; b_opt = newb;
		  }
		}
    }

	public static void main(String[] args)
	{
		int runs;
		kevin6 sol = new kevin6(1,1);
		int n;

		Scanner in = new Scanner(System.in);
		
		runs = in.nextInt();


		while (runs-- != 0)
		{
			n = in.nextInt();

			sol.findBase(n);
			System.out.println(sol.a_opt + " " + sol.b_opt);
		}
	}
}