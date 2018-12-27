// Solution to Growling Gears
// Author: Kevin Buchin

// Time complexity: ...
// Memory: O(1)

// @EXPECTED_RESULTS@: CORRECT

// binary search for max per gear



import java.util.Scanner;
//import java.math.BigInteger;

public class kevin {

	public static void main(String[] args)
	{
		int runs;
		Scanner in = new Scanner(System.in);
		runs = in.nextInt();

		while (runs-- != 0)
		{
			int ngears = in.nextInt();
			
			long maxTorqueNom = -1;
			long maxTorqueDenom = 1;
			
			//long maxRPM = -1;
			
			long curTorqueNom;
			long curTorqueDenom;

			
			int maxGear = 0;
			
			long a, b, c;
			
			for(int i = 0; i< ngears; i++) {
				a = in.nextLong();
				b = in.nextLong();
				c = in.nextLong();
				
				curTorqueNom = b*b + 4*a*c;
				curTorqueDenom = 4*a;
				
				if (curTorqueNom*maxTorqueDenom > maxTorqueNom*curTorqueDenom) {
					maxTorqueNom = curTorqueNom;
					maxTorqueDenom = curTorqueDenom;
					//maxRPM =(b+a)/(2*a);
					maxGear = i+1;
				}
			}

			System.out.println(maxGear); // + " " + maxRPM);

		}
	}
}
