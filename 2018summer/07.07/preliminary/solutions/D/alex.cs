// Implements quadratic-time, linear-space, dynamic-programming solution
// Adapted from herman-correct.cpp by Alex
// @EXPECTED_RESULTS@: CORRECT

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BAPC
{
	public static class Program
	{
		public static int[] ReadInts()
		{
			return Console.ReadLine().Split(' ').Select(s => int.Parse(s)).ToArray();
		}
		public static int MAXFLOORS = 1500;
		public static int MAXPERFLOOR = 1500;
		public static uint MAXANGER = 1u << 31;
		public static void Main(string[] args)
		{
			int nrTestCases = ReadInts()[0];
			while (--nrTestCases >= 0)
			{
				int nrFloors = ReadInts()[0];
				// table to maintain number of students for given and lower floors:
				uint[] students = new uint[MAXFLOORS+1];
				students[0] = 0;
				int[] inputs = ReadInts();
				for (int i = 1; i <= nrFloors; ++i)
				{
					students[i] = (uint)inputs[i-1];
					students[i] += students[i-1];
				}
				// table to maintain anger up to and including current floor if last stop is on given floor
				// note: annoyance for skipping is counted starting with the floor of destination, and not for the floor where students get out
				uint[] anger = new uint[MAXFLOORS+1];
				anger[0] = 0;
				for (int currentFloor = 1; currentFloor <= nrFloors; ++currentFloor)
				{
					anger[currentFloor] = MAXANGER;
					for (int lastStop = 0; lastStop < currentFloor; ++lastStop)
					{
						anger[currentFloor] = Math.Min(anger[currentFloor], anger[lastStop] + students[nrFloors] - students[currentFloor]);
						anger[lastStop] += students[currentFloor] - students[lastStop];      
					}
				}
				Console.WriteLine(anger[nrFloors]);
			}
		}
	}
}
