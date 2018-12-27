// Implements quadratic-time, linear-space, dynamic-programming solution
// Adapted from herman-correct.cpp by Alex
// @EXPECTED_RESULTS@: CORRECT

import java.util.Scanner;

public class alex
{
	public static int MAXFLOORS = 1500;
	public static int MAXPERFLOOR = 1500;
	public static long MAXANGER = 1l << 31;
	public static void main(String[] args)
	{
		Scanner in = new Scanner(System.in);
		int nrTestCases = in.nextInt();
		while (--nrTestCases >= 0)
		{
			int nrFloors = in.nextInt();
			// table to maintain number of students for given and lower floors:
			int[] students = new int[MAXFLOORS+1];
			students[0] = 0;
			for (int i = 1; i <= nrFloors; ++i)
			{
				students[i] = in.nextInt();
				students[i] += students[i-1];
			}
			// table to maintain anger up to and including current floor if last stop is on given floor
			// note: annoyance for skipping is counted starting with the floor of destination, and not for the floor where students get out
			long[] anger = new long[MAXFLOORS+1];
			anger[0] = 0;
			for (int currentFloor = 1; currentFloor <= nrFloors; ++currentFloor)
			{
				anger[currentFloor] = MAXANGER;
				for (int lastStop = 0; lastStop < currentFloor; ++lastStop)
				{
					anger[currentFloor] = Math.min(anger[currentFloor], anger[lastStop] + students[nrFloors] - students[currentFloor]);
					anger[lastStop] += students[currentFloor] - students[lastStop];      
				}
			}
			System.out.println(anger[nrFloors]);
		}
	}
}
