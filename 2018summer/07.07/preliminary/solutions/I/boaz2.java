// @EXPECTED_RESULTS@: TIMELIMIT
import java.io.*;
import java.util.*;

public class boaz2 {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	public static void main(String[] args) throws Exception {
		log = false;
		if (args.length > 0) {
			out(args[0]);
			if (args[0].toLowerCase().equals("-log")) {
				log = true;
				if (args.length > 1)
					logCase = Integer.parseInt(args[1]);
				else logCase = 0;
			}
		}
		String testcases = in.readLine();
		int cases = Integer.parseInt(testcases);

		for (int i = 0; i < cases; i++) {
			caseNumber = i + 1;
			System.out.println("" + solve());
		}
	}

	static Tunnel tunnel;
	static ArrayList<Person> people;
	static ArrayList<Person> peopleMovingLeft;
	static ArrayList<Person> peopleMovingRight;
	static int ticks;
	static boolean log;
	static int logCase;
	static int caseNumber;

	static void out(String s) {
		System.out.println(s);
	}

	static int solve() throws Exception {
		String firstLine = in.readLine();
		int p;
		{
			String[] firstLineSplit = firstLine.split(" ");
			int w = Integer.parseInt(firstLineSplit[0]);
			int h = Integer.parseInt(firstLineSplit[1]);
			p = Integer.parseInt(firstLineSplit[2]);

			tunnel = new Tunnel(w, h);
		}
		people = new ArrayList<Person>();
		peopleMovingLeft = new ArrayList<Person>();
		peopleMovingRight = new ArrayList<Person>();

		for (int i = 0; i < p; i++) {
			String nextLine = in.readLine();
			String[] nextLineSplit = nextLine.split(" ");
			int x = Integer.parseInt(nextLineSplit[0]);
			int y = Integer.parseInt(nextLineSplit[1]);
			int s = Integer.parseInt(nextLineSplit[2]);
			char d = nextLineSplit[3].charAt(0);

			Person person = new Person(x, y, s, d, i + 1);
			if (d == 'L')
				peopleMovingLeft.add(person);
			else peopleMovingRight.add(person);
			people.add(person);

		}

		return doProblem();
	}

	static int doProblem() {
		Collections.sort(peopleMovingLeft, new RightToLeft());
		Collections.sort(peopleMovingRight, new LeftToRight());

		ticks = 0;
		while (people.size() > 0) {
			ticks++;
			if (doLog()) out("time " + ticks);
			tick();
		}
		return ticks;
	}

	static boolean doLog() {
		return log && (logCase == 0 ? true : (logCase == caseNumber));
	}

	static void tick() {
		ArrayList annoyedPeople = new ArrayList<Person>();
		boolean peopleMoved = false;
		// Move people from left to right
		for (int i = 0; i < peopleMovingRight.size(); i++) {
			Person p = (Person)peopleMovingRight.get(i);
			p.annoyed = false;

			// Move right
			Target t = new Target();
			t.x = p.x + p.s;
			t.y = p.y;

			ArrayList inFront = peopleInFront(p, t);
			Person bump = (Person)personInFront(p.d, inFront);
			if (bump != null) {
				t.x = bump.x - 1;
				p.annoyed = (t.x - p.x) <= p.hs;
			}

			p.x = t.x;
			p.y = t.y;

			if (doLog()) {
				if (!p.annoyed) // Lelijke code
					out(p.i + " walks to (" + t.x + "," + t.y + ")");
				else out(p.i + " walks to (" + t.x + "," + t.y + ") and is annoyed");
			}

			if (p.x > tunnel.w) {
				p.freedom = true;
				if (doLog()) out(p.i + " leaves tunnel");
			}

			if (p.annoyed && !p.freedom) annoyedPeople.add(p);
		}

		// Move people from right to left
		for (int i = 0; i < peopleMovingLeft.size(); i++) {
			Person p = peopleMovingLeft.get(i);
			p.annoyed = false;

			// Move left
			Target t = new Target();
			t.x = p.x - p.s;
			t.y = p.y;

			ArrayList inFront = peopleInFront(p, t);
			Person bump = (Person)personInFront(p.d, inFront);
			if (bump != null) {
				t.x = bump.x + 1;
				p.annoyed = (p.x - t.x) <= p.hs;
			}

			p.x = t.x;
			p.y = t.y;

			if (doLog()) {
				if (!p.annoyed) // Lelijke code
					out(p.i + " walks to (" + t.x + "," + t.y + ")");
				else out(p.i + " walks to (" + t.x + "," + t.y + ") and is annoyed");
			}

			if (p.x <= 0) {
				p.freedom = true;
				if (doLog()) out(p.i + " leaves tunnel");
			}

			if (p.annoyed && !p.freedom) annoyedPeople.add(p);
		}

		// Move annoyed people
		Collections.sort(annoyedPeople, new TopToBottom());

		// First, from top to bottom, every annoyed person moving to the right will try to take a step left (that person's left, so up)
		for (int i = 0; i < annoyedPeople.size(); i++) {
			Person p = (Person)annoyedPeople.get(i);
			if (p.d == 'L') continue;
			if (p.y <= 1) continue;
			if (!blocked(p.x, p.y - 1)) {
				p.y -= 1;
				p.annoyed = false;
				if (doLog()) out(p.i + " steps left to (" + p.x + "," + p.y + ")");
			}
		}

		// Then, from bottom to top, every annoyed person moving left will try to step left.
		for (int i = annoyedPeople.size() - 1; i >= 0; i--) {
			Person p = (Person)annoyedPeople.get(i);
			if (p.d == 'R') continue;
			if (p.y >= tunnel.h) continue;
			if (!blocked(p.x, p.y + 1)) {
				p.y += 1;
				p.annoyed = false;
				if (doLog()) out(p.i + " steps left to (" + p.x + "," + p.y + ")");
			}
		}

		// Then from bottom to top every annoyed person moving right who was unable to step left ('still annoyed') will try to step right.
		for (int i = annoyedPeople.size() - 1; i >= 0; i--) {
			Person p = (Person)annoyedPeople.get(i);
			if (!p.annoyed) continue;
			if (p.d == 'L') continue;
			if (p.y >= tunnel.h) continue;
			if (!blocked(p.x, p.y + 1)) {
				p.y += 1;
				p.annoyed = false;
				if (doLog()) out(p.i + " steps right to (" + p.x + "," + p.y + ")");
			}
		}
		
		// Finally, from top to bottom every still annoyed person moving left will try to step right.
		for (int i = 0; i < annoyedPeople.size(); i++) {
			Person p = (Person)annoyedPeople.get(i);
			if (!p.annoyed) continue;
			if (p.d == 'R') continue;
			if (p.y <= 1) continue;
			if (!blocked(p.x, p.y - 1)) {
				p.y -= 1;
				p.annoyed = false;
				if (doLog()) out(p.i + " steps right to (" + p.x + "," + p.y + ")");
			}
		}

		// Remove all freed people
		Iterator it = peopleMovingLeft.iterator();
		while (it.hasNext()) {
			Person p = (Person)it.next();
			if (p.freedom)
				it.remove();
		}
		it = peopleMovingRight.iterator();
		while (it.hasNext()) {
			Person p = (Person)it.next();
			if (p.freedom)
				it.remove();
		}
		it = people.iterator();
		while (it.hasNext()) {
			Person p = (Person)it.next();
			if (p.freedom)
				it.remove();
		}

		// Sort people
		Collections.sort(peopleMovingLeft, new RightToLeft());
		Collections.sort(peopleMovingRight, new LeftToRight());
	}

	static boolean blocked(int x, int y) {
		for (int i = 0; i < people.size(); i++) {
			Person p = people.get(i);
			if (p.x == x && p.y == y) return true;
		}
		return false;
	}

	static ArrayList peopleInFront(Person p, Target t) {
		ArrayList peopleInFront = new ArrayList();
		for (int j = 0; j < people.size(); j++) {
			Person o = people.get(j);
			if (p == o) continue;
			if (p.y != o.y) continue;
			//if (o.x < 0 || o.x > tunnel.w) continue;
			if (p.d == 'R') {
				if (o.x > p.x && o.x <= t.x) peopleInFront.add(o);
			}
			else if (o.x >= t.x && o.x < p.x) peopleInFront.add(o);
		}

		return peopleInFront;
	}

	static Person personInFront(char d, ArrayList inFront) {
		if (inFront.size() == 0) return null;

		Person personToBumpInto = (Person)inFront.get(0);
		if (d == 'R') {
			for (int i = 0; i < inFront.size(); i++) {
				if (((Person)inFront.get(i)).x < personToBumpInto.x)
					personToBumpInto = (Person)inFront.get(i);
			}
		}
		if (d == 'L') {
			for (int i = 0; i < inFront.size(); i++) {
				if (((Person)inFront.get(i)).x > personToBumpInto.x)
					personToBumpInto = (Person)inFront.get(i);
			}
		}

		return personToBumpInto;
	}

	static class Tunnel {
		public int w, h;

		public Tunnel(int _w, int _h) {
			w = _w;
			h = _h;
		}
	}

	public static class Target {
		public int x, y;
		public Target() {
			x = 0;
			y = 0;
		}

		public Target(int _x, int _y) {
			x = _x;
			y = _y;
		}
	}

	public static class Person {
		public int x, y, s, hs, i;
		public char d;
		public boolean annoyed;
		public boolean freedom;

		public Person(int _x, int _y, int _s, char _d, int _i) {
			annoyed = false;
			freedom = false;
			x = _x;
			y = _y;
			s = _s;
			d = _d;
			i = _i;
			hs = _s / 2 + (_s % 2 == 1 ? 1 : 0);
		}
	}

	public static class LeftToRight implements Comparator<Person> {
		public int compare(Person p1, Person p2) {
			return new Integer(-p1.x).compareTo(new Integer(-p2.x));
		} 
	}

	public static class RightToLeft implements Comparator<Person> {
		public int compare(Person p1, Person p2) {
			return new Integer(p1.x).compareTo(new Integer(p2.x));
		} 
	}

	public static class TopToBottom implements Comparator<Person> {
		public int compare(Person p1, Person p2) {
			return new Integer(p1.y).compareTo(new Integer(p2.y));
		} 
	}
}
