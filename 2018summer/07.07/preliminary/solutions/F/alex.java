// Solution to Runway planning
// Author: Pieter Bootsma, converted to Java by Alex ten Brink

// Time complexity: O(1)
// Memory: O(1)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: calculate it

import java.util.Scanner;

public class alex
{
	public static void main(String[] args)
	{
		Scanner in = new Scanner(System.in);
		int runs = in.nextInt();
		for (int i = 0; i < runs; i++)
		{
			int heading = in.nextInt();

			// Divide by 10, rounding as appropiate
			int runway = (heading + 5) / 10;

			// Limit to range [0,17]
			runway %= 18;

			// Limit to range [1,18]
			if (runway == 0)
			{
				runway = 18;
			}

			// Print leading 0 if less than 10
			if (runway < 10)
			{
				System.out.print(0);
			}

			// Print runway number
			System.out.println(runway);
		}
	}
}

