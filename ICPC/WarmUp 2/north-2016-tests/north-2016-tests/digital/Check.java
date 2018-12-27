/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem D. Digital Addition                                    */
/*                                                                */
/* Original idea         Mikhail Dvorkin                          */
/* Problem statement     Mikhail Dvorkin                          */
/* Test set              Mikhail Dvorkin                          */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author                Mikhail Dvorkin                          */
/******************************************************************/

import ru.ifmo.testlib.*;
import static ru.ifmo.testlib.Outcome.Type.*;

import java.math.BigInteger;

public class Check implements Checker {
	public static final String NO = "NO";
	public static final String[] DIGITAL = new String[]{
			"+++ +++",
			"  +  + ",
			"+ +++ +",
			"+ ++ ++",
			" +++ + ",
			"++ + ++",
			"++ ++++",
			"+ +  + ",
			"+++++++",
			"++++ ++",
	};

	@Override
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		String[] jAns = new String[3];
		jAns[0] = ans.nextLine();
		boolean jNo = NO.equals(jAns[0]); 
		if (!jNo) {
			jAns[1] = ans.nextLine();
			jAns[2] = ans.nextLine();
		}
		
		String[] cAns = new String[3];
		cAns[0] = ouf.nextLine();
		if (NO.equals(cAns[0])) {
			if (jNo) {
				return new Outcome(OK, "Answer is " + NO);
			}
			return new Outcome(WA, NO + " found, but there is a correct addition");
		}
		cAns[1] = ouf.nextLine();
		cAns[2] = ouf.nextLine();
		
		int w = inf.nextInt();
		inf.nextLine();
		for (int i = 0; i < 3; i++) {
			if (cAns[i].length() != w) {
				return new Outcome(PE, "Wrong length of line: " + cAns[i].length());
			}
			if (!cAns[i].matches("^[0-9]*$")) {
				return new Outcome(PE, "Non-digit chars found in: " + cAns[i]);
			}
		}
		if (!new BigInteger(cAns[0]).add(new BigInteger(cAns[1])).equals(new BigInteger(cAns[2]))) {
			return new Outcome(WA, "1st + 2nd != 3rd");
		}
		
		boolean[][] picture = new boolean[9][w + 1];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < w; j++) {
				String digit = DIGITAL[cAns[i].charAt(j) - '0'];
				picture[2 * i][j] |= digit.charAt(0) == '+';
				picture[2 * i + 1][j] |= digit.charAt(1) == '+';
				picture[2 * i + 1][j + 1] |= digit.charAt(2) == '+';
				picture[2 * i + 2][j] |= digit.charAt(3) == '+';
				picture[2 * i + 3][j] |= digit.charAt(4) == '+';
				picture[2 * i + 3][j + 1] |= digit.charAt(5) == '+';
				picture[2 * i + 4][j] |= digit.charAt(6) == '+';
			}
		}
		
		for (int i = 0; i < 9; i++) {
			int len = w + i % 2;
			for (int j = 0; j < len; j++) {
				int segment = inf.nextInt();
				if ((segment == 1) ^ picture[i][j]) {
					return new Outcome(WA, "Picture differs in line " + (i + 1) + ", column " + (j + 1));
				}
			}
		}
		if (jNo) {
			return new Outcome(FAIL, "Solution found, but jury had " + NO);
		}
		return new Outcome(OK, "Correct addition found");
	}
}

