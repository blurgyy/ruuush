// Solution to Growling Gears
// Author: Pieter Bootsma

// Time complexity: O(n)
// Memory: O(1)

// @EXPECTED_RESULTS@: CORRECT

// Solution method: calculate top of each parabola, compare to others

#include <iostream>

using namespace std;

void dostep()
{
	// Read number of gears
	int nr_gears;
	cin >> nr_gears;
	
	// Loop over all gears in input and find gear producing max torque
	int max_gear = 0;
	double max_rpm = 0;
	double max_torque = -1;
	
	for (int gear = 1; gear <= nr_gears; gear++)
	{
		// Read parabola parameters
		double a,b,c;
		cin >> a >> b >> c;
		
		// Calculate top of parabola, and torque at that point
		double rpm = b / (2 * a);
		double torque = -a*rpm*rpm + b*rpm + c;
		
		// Check if we reached a new torque maximum
		if (torque > max_torque + 1e-6)
		{
			max_gear = gear;
			max_rpm = rpm;
			max_torque = torque;
		}
	}
	
	// Print maximum gear/rpm
	int rounded_max_rpm = max_rpm + .5;
	cout << max_gear << endl; //' ' << rounded_max_rpm << endl;
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
