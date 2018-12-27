// Solution to Interesting Integers
// Author: Kevin Buchin, port of kevin1.cpp

// Time complexity: O(log(n))
// Memory: O(log(n)), but this wouldn't be needed

// @EXPECTED_RESULTS@: CORRECT

// Solution method: solve a*Fib[i-2] + b*Fib[i-1]  for all sufficiently small i

import java.util.Scanner;

public class kevin5 {

	private static final int[] Fib = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296, 433494437, 701408733, 1134903170};
	private static int nFib = 46;
	int a_opt, b_opt;

	public kevin5(int a, int b) {
	this.a_opt = a;
	this.b_opt = b;
	}


	public void findBase(int n)
	{
		int new_a;
		int t;

		int a = n / 2;
		int b = n - a;
		
		a_opt = a;
		b_opt = b;

		for (int i = 2; i < nFib - 2; i++)
		{
			t = (2 * a - b) / Fib[i + 2];

			// if the unrounded t is negative and non-integral, we round t down by hand
			if ((2 * a < b) && ((2 * a - b) % Fib[i + 2] != 0))
			{
				t--;
			}

			new_a = b - a + t * Fib[i + 1];
			if (new_a <= 0) return;
			else
			{
				b = a - t * Fib[i];
				a = new_a;

				if ((b < b_opt) || ((b == b_opt) && (a < a_opt)))
				{
					b_opt = b;
					a_opt = a;
				}
			}

		}
	}

	public static void main(String[] args)
	{
		int runs;
		kevin5 sol = new kevin5(1,1);
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