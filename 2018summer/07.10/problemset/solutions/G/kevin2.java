// Solution to Growling Gears
// Author: Kevin Buchin

// Time complexity: O(n)
// Memory: O(1)

// @EXPECTED_RESULTS@: CORRECT

// this solution is wrong if rounding issues play a role, but works with the new description

import java.util.Scanner;
//import java.math.BigInteger;

public class kevin2 {

	public static void main(String[] args)
	{
		int runs;
		int run = 0;
		
		Scanner in = new Scanner(System.in);
		runs = in.nextInt();

		while (run++ < runs)
		{
			int ngears = in.nextInt();
			
			double maxTorque = -1.0;
			double max2Torque = -1.0;
			
			double curTorque;

			int maxGear = 0;
			//int max2Gear = 0;
			
			int a, b, c;
			
			for(int i = 0; i< ngears; i++) {
				a = in.nextInt();
				b = in.nextInt();
				c = in.nextInt();
				
				curTorque = b*b/4/a + c;
				
				if (curTorque > maxTorque) {
					max2Torque = maxTorque;
					
					maxTorque = curTorque;
					maxGear = i+1;
				} else if (curTorque > max2Torque) {
					max2Torque = curTorque;
				}
			}

			if (maxTorque-max2Torque < 1.00000000001) System.err.println("In test case " + run + ": diff between max and 2nd is only " + (maxTorque-max2Torque) ); 
			
			System.out.println(maxGear); 

		}
	}
}
