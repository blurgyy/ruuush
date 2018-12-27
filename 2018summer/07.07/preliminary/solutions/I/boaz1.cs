// @EXPECTED_RESULTS@: TIMELIMIT
﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ArrayList = System.Collections.Generic.List<Person>;

public class boaz1 {
	public static void Main(string[] args) {
		string testcases = Console.In.ReadLine();
		int cases = Int32.Parse(testcases);

		for (int i = 0; i < cases; i++)
			Console.WriteLine(solve());
		Console.In.Close();
	}

	public const int MIN_X = 1;
	public const int MIN_Y = 1;
	public const int MAX_X = 3000;
	public const int MAX_Y = 1000;
	public const int MIN_S = 1;
	public const int MAX_S = 1000;
	public const int MIN_W = 1;
	public const int MIN_H = 1;
	public const int MAX_W = 3000;
	public const int MAX_H = 1000;
	public const int MIN_P = 1;
	public const int MAX_P = 1000;

	static Tunnel tunnel;
	static ArrayList people;
	static ArrayList peopleMovingLeft;
	static ArrayList peopleMovingRight;
	static int ticks;

	static int solve() {
		String firstLine = Console.In.ReadLine();
		int p;
		{
			var firstLineSplit = firstLine.Split(new char[] { ' ' });
			int w = Int32.Parse(firstLineSplit[0]);
			int h = Int32.Parse(firstLineSplit[1]);
			p = Int32.Parse(firstLineSplit[2]);

			if (w < MIN_W || w > MAX_W) throw new Exception("Input error: Invalid value for 'w'");
			if (h < MIN_H || h > MAX_H) throw new Exception("Input error: Invalid value for 'h'");
			if (p < MIN_P || p > MAX_P) throw new Exception("Input error: Invalid value for 'p'");

			tunnel = new Tunnel(w, h);
		}
		people = new ArrayList();
		peopleMovingLeft = new ArrayList();
		peopleMovingRight = new ArrayList();

		for (int i = 0; i < p; i++) {
			String nextLine = Console.In.ReadLine();
			var nextLineSplit = nextLine.Split(new char[] { ' ' });
			int x = Int32.Parse(nextLineSplit[0]);
			int y = Int32.Parse(nextLineSplit[1]);
			int s = Int32.Parse(nextLineSplit[2]);
			char d = nextLineSplit[3][0];

			Person person = new Person(x, y, s, d);
			try {
				if (person.x > tunnel.w)
					throw new Exception(string.Format("Input error: person.x > l! {0}, {1}", person.x, tunnel.w));
				if (person.y > tunnel.h)
					throw new Exception(string.Format("Input error: person.y > w! {0}, {1}", person.y, tunnel.h));
			}
			catch (Exception e) {
				Console.WriteLine(e.Message);
			}

			if (d == 'L')
				peopleMovingLeft.Add(person);
			else peopleMovingRight.Add(person);
			if (people.FirstOrDefault(pe => pe.x == person.x && pe.y == person.y) != null)
				throw new Exception("Input error: Multiple persons on same gridpoint");
			people.Add(person);

		}

		return doProblem();
	}

	static int doProblem() {
		peopleMovingLeft.Sort(delegate(Person p1, Person p2) { return p1.x.CompareTo(p2.x); });
		peopleMovingRight.Sort(delegate(Person p1, Person p2) { return -p1.x.CompareTo(p2.x); });

		ticks = 0;
		while (people.Count() > 0) {
			ticks++;
			tick();
		}
		return ticks;
	}

	static void tick() {
		ArrayList annoyedPeople = new ArrayList();
		bool peopleMoved = false;
		// Move people from left to right
		for (int i = 0; i < peopleMovingRight.Count(); i++) {
			Person p = peopleMovingRight[i];
			p.annoyed = false;

			// Move right
			Target t;
			t.x = p.x + p.s;
			t.y = p.y;

			ArrayList inFront = peopleInFront(p, t);
			Person bump = personInFront(p.d, inFront);
			if (bump != null) {
				t.x = bump.x - 1;
				p.annoyed = (t.x - p.x) <= p.hs;
			}

			p.x = t.x;
			p.y = t.y;

			if (p.x > tunnel.w)
				p.freedom = true;

			if (p.annoyed && !p.freedom) annoyedPeople.Add(p);
		}

		// Move people from right to left
		for (int i = 0; i < peopleMovingLeft.Count(); i++) {
			Person p = peopleMovingLeft[i];
			p.annoyed = false;

			// Move left
			Target t;
			t.x = p.x - p.s;
			t.y = p.y;

			ArrayList inFront = peopleInFront(p, t);
			Person bump = personInFront(p.d, inFront);
			if (bump != null) {
				t.x = bump.x + 1;
				p.annoyed = (p.x - t.x) <= p.hs;
			}


			p.x = t.x;
			p.y = t.y;

			if (p.x <= 0)
				p.freedom = true;
			if (p.annoyed && !p.freedom) annoyedPeople.Add(p);
		}

		// Move annoyed people
		annoyedPeople.Sort(delegate(Person p1, Person p2) { return p1.y.CompareTo(p2.y); });

		// First, from top to bottom, every annoyed person moving to the right will try to take a step left (that person's left, so up)
		for (int i = 0; i < annoyedPeople.Count(); i++) {
			Person p = annoyedPeople[i];
			if (p.d == 'L') continue;
			if (p.y <= 1) continue;
			if (!blocked(p.x, p.y - 1)) {
				p.y -= 1;
				p.annoyed = false;
			}
		}

		// Then, from bottom to top, every annoyed person moving left will try to step left.
		for (int i = annoyedPeople.Count() - 1; i >= 0; i--) {
			Person p = annoyedPeople[i];
			if (p.d == 'R') continue;
			if (p.y >= tunnel.h) continue;
			if (!blocked(p.x, p.y + 1)) {
				p.y += 1;
				p.annoyed = false;
			}
		}

		// Then from bottom to top every annoyed person moving right who was unable to step left ('still annoyed') will try to step right.
		for (int i = annoyedPeople.Count() - 1; i >= 0; i--) {
			Person p = annoyedPeople[i];
			if (!p.annoyed) continue;
			if (p.d == 'L') continue;
			if (p.y >= tunnel.h) continue;
			if (!blocked(p.x, p.y + 1)) {
				p.y += 1;
				p.annoyed = false;
			}
		}

		// Finally, from top to bottom every still annoyed person moving left will try to step right.
		for (int i = 0; i < annoyedPeople.Count(); i++) {
			Person p = annoyedPeople[i];
			if (!p.annoyed) continue;
			if (p.d == 'R') continue;
			if (p.y <= 1) continue;
			if (!blocked(p.x, p.y - 1)) {
				p.y -= 1;
				p.annoyed = false;
			}
		}

		// Remove all freed people
		peopleMovingLeft.RemoveAll(p => p.freedom);
		peopleMovingRight.RemoveAll(p => p.freedom);
		people.RemoveAll(p => p.freedom);

		// Sort people
		peopleMovingLeft.Sort(delegate(Person p1, Person p2) { return p1.x.CompareTo(p2.x); });
		peopleMovingRight.Sort(delegate(Person p1, Person p2) { return -p1.x.CompareTo(p2.x); });
	}

	static bool blocked(int x, int y) {
		for (int i = 0; i < people.Count(); i++) {
			Person p = people[i];
			if (p.x == x && p.y == y) return true;
		}
		return false;
	}

	static ArrayList peopleInFront(Person p, Target t) {
		ArrayList peopleInFront = new ArrayList();
		for (int j = 0; j < people.Count(); j++) {
			Person o = people[j];
			if (p == o) continue;
			if (p.y != o.y) continue;
			//if (o.x < 0 || o.x > tunnel.w) continue;

			if (p.d == 'R') {
				if (o.x > p.x && o.x <= t.x) peopleInFront.Add(o);
			}
			else if (o.x >= t.x && o.x < p.x) peopleInFront.Add(o);
		}

		return peopleInFront;
	}

	static Person personInFront(char d, ArrayList inFront) {
		if (inFront.Count == 0) return null;

		Person personToBumpInto = inFront[0];
		if (d == 'R') {
			for (int i = 0; i < inFront.Count(); i++) {
				if (inFront[i].x < personToBumpInto.x)
					personToBumpInto = inFront[i];
			}
		}
		if (d == 'L') {
			for (int i = 0; i < inFront.Count(); i++) {
				if (inFront[i].x > personToBumpInto.x)
					personToBumpInto = inFront[i];
			}
		}

		return personToBumpInto;
	}
}

class Tunnel {
	public int w, h;

	public Tunnel(int _w, int _h) {
		w = _w;
		h = _h;
	}
}

public struct Target {
	public int x, y;
	public Target(int _x, int _y) {
		x = _x;
		y = _y;
	}
}

public class Person {
	public int x, y, s, hs;
	public char d;
	public bool annoyed;
	public bool freedom;

	public Person(int _x, int _y, int _s, char _d) {
		if (_d != 'L' && _d != 'R') throw new Exception("Input error: Unknown direction " + _d);
		if (_x < boaz1.MIN_X || _x > boaz1.MAX_X) throw new Exception("Input error: Invalid value for 'x'");
		if (_y < boaz1.MIN_Y || _y > boaz1.MAX_Y) throw new Exception("Input error: Invalid value for 'y'");
		if (_s < boaz1.MIN_S || _s > boaz1.MAX_S) throw new Exception("Input error: Invalid value for 's'");

		annoyed = false;
		freedom = false;
		x = _x;
		y = _y;
		s = _s;
		d = _d;
		hs = _s / 2 + (_s % 2 == 1 ? 1 : 0);
	}
}
