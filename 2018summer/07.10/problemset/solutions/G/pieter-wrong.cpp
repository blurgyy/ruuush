// Solution to Growling Gears
// Author: Pieter Bootsma

// Time complexity: O(n)
// Memory: O(1)

// @EXPECTED_RESULTS@: WRONG-ANSWER

// Solution method: calculate top of each parabola with integers, compare to others

#include <iostream>

using namespace std;

void dostep()
{
	// Read number of gears
	int nr_gears;
	cin >> nr_gears;
	
	// Loop over all gears in input and find gear producing max torque
	int max_gear = 0;
	int max_rpm = 0;
	int max_torque = -1;
	
	for (int gear = 1; gear <= nr_gears; gear++)
	{
		// Read parabola parameters
		int a,b,c;
		cin >> a >> b >> c;
		
		// Calculate top of parabola, and torque at that point
		int rpm = b / (2 * a);
		int torque = -a*rpm*rpm + b*rpm + c;
		
		// Check if we reached a new torque maximum
		if (torque > max_torque)
		{
			max_gear = gear;
			max_rpm = rpm;
			max_torque = torque;
		}
	}
	
	// Print maximum gear/rpm
	cout << max_gear << endl; //' ' << max_rpm << endl;
}

int main(int, char**)
{
	int n;
	cin >> n;
	while (n--)
	{
		dostep();
	}
	
	return 0;
}
