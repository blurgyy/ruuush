// @EXPECTED_RESULTS@: CORRECT

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ArrayList = System.Collections.Generic.List<char>;

public class Maze {
	public enum Direction {
		Up, Right, Down, Left
	}

	static void Main(string[] args) {
		string testcases = Console.In.ReadLine();
		int cases = Int32.Parse(testcases);

		Console.Out.WriteLine(cases);

		for (int i = 0; i < cases; i++)
			solve();
	}

	static int x, y, t, b, r;
	static Direction dir;
	private static void solve() {
		string movement = Console.In.ReadLine();
		char[,] maze = new char[100, 300];

		for (int _y = 0; _y < 300; _y++)
			for (int _x = 0; _x < 100; _x++) {
				maze[_x, _y] = '#';
			}

		x = 0;
		y = 100;
		t = 300;
		b = 0;
		r = 0;
		dir = Direction.Right;

		for (int i = 0; i < movement.Length; i++) {
			char move = movement[i];
			if (move != 'F' && move != 'L' && move != 'R' && move != 'B') throw new IndexOutOfRangeException("Input error: Wrong movement in input: '" + move + ".");
			changeDir(move);
			moveRobot();
			maze[x, y] = '.';
			if (y < t) t = y;
			if (y > b) b = y;
			if (x > r) r = x;
		}

		Console.Out.WriteLine("{0} {1}", (b + 2) - (t - 1), r + 2);
		for (int _y = t - 1; _y < b + 2; _y++) {
			for (int _x = 0; _x < r + 2; _x++)
				Console.Out.Write(maze[_x, _y]);
			Console.Out.Write('\n');
		}
	}

	private static void moveRobot() {
		switch (dir) {
			case Direction.Up: y--; break;
			case Direction.Right: x++; break;
			case Direction.Down: y++; break;
			case Direction.Left: x--; break;
		}
	}

	private static void changeDir(char move) {
		switch (dir) {
			case Direction.Up:
				switch (move) {
					case 'F': break;
					case 'L': dir = Direction.Left; break;
					case 'R': dir = Direction.Right; break;
					case 'B': dir = Direction.Down; break;
				}
				break;
			case Direction.Right:
				switch (move) {
					case 'F': break;
					case 'L': dir = Direction.Up; break;
					case 'R': dir = Direction.Down; break;
					case 'B': dir = Direction.Left; break;
				}
				break;
			case Direction.Down:
				switch (move) {
					case 'F': break;
					case 'L': dir = Direction.Right; break;
					case 'R': dir = Direction.Left; break;
					case 'B': dir = Direction.Up; break;
				}
				break;
			case Direction.Left:
				switch (move) {
					case 'F': break;
					case 'L': dir = Direction.Down; break;
					case 'R': dir = Direction.Up; break;
					case 'B': dir = Direction.Right; break;
				}
				break;
		}
	}

}

