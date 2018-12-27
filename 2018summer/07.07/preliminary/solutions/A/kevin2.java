// Solution to Icecream
// Author: Kevin Buchin

// Time complexity: O(log(n))
// Memory: O(1)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: testing k^i/N \in \N, but using modulo excessively
// port of my c++ solution



import java.util.Scanner;
//import java.math.BigInteger;

public class kevin2 {

	public static void main(String[] args)
	{
		int runs;
		Scanner in = new Scanner(System.in);
		runs = in.nextInt();

		while (runs-- != 0)
		{
			long n;
			long k;
			long r;

			// Read input
			n = in.nextInt();
			k = in.nextInt();

			r = 1 % n;
			k = k % n;

			for (int i = 0; i <= 32; i++)
			{
				if (r == 0)
				{
					System.out.print(i);
					System.out.print("\n");
					break;
				}
				r = (r * k) % n;
			}
			if (r != 0)
			{
				System.out.print("unbounded");
				System.out.print("\n");
			}
		}
	}
}
