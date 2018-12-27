/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem J. Java2016                                            */
/*                                                                */
/* Original idea         Georgiy Korneev                          */
/* Problem statement     Georgiy Korneev                          */
/* Test set              Georgiy Korneev                          */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author                Georgiy Korneev                          */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.function.IntBinaryOperator;

import static java.util.Arrays.stream;
import static ru.ifmo.testlib.Outcome.Type.FAIL;
import static ru.ifmo.testlib.Outcome.Type.OK;
import static ru.ifmo.testlib.Outcome.Type.WA;

public class Check implements Checker {
    private static final int MODULO = 256;
    private static final int MAX_LEN = 256;
    private static final double[] RANDOM = new double[MODULO + 1];
    static {
        Arrays.fill(RANDOM, 0, MODULO, 1.0 / MODULO);
    }

    private double[][] macros = new double[26][];
    private int pos = 0;
    private String line;
    private int lineNo = 0;
    private char curChar;

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        int total = 0;
        while (true) {
            line = ouf.nextLine().replace(" ", "") + "$$";
            pos = 0;
            lineNo++;
            nextChar();
            total += line.length() - 2;
            if (total > MAX_LEN) {
                return new Outcome(WA, "Program length exceeds " + MAX_LEN);
            }

            if (line.contains("=")) {
                parseMacrodef();
            } else {
                break;
            }

        }
        final double[] expression = parseExpression();
        final int target = inf.nextInt();
        double discrepancy = Math.abs(1 - stream(expression).sum());
        if (discrepancy > 1e-10) {
            throw new Outcome(FAIL, String.format("discrepancy %g", discrepancy));
        }
        final String result = String.format("Probability of %d is %.10f (error %f, discrepancy %g, length %d)", target, expression[target], expression[MODULO], discrepancy, total);
        return new Outcome(expression[target] >= 0.5 - discrepancy ? OK : WA, result);
    }

    private void parseMacrodef() {
        int macro = parseMacro();
        expect('=');
        if (macros[macro] != null) {
            throw error("Macro '%c' redefined", macro + 'a');
        }
        macros[macro] = parseExpression();
        expect('$');
    }

    private enum Operation {
        MIN(Integer::min),
        MAX(Integer::max),
        MUL((a, b) -> (a * b) % MODULO),
        DIV((a, b) -> b == 0 ? MODULO : a / b),
        ADD((a, b) -> (a + b) % MODULO),
        SUB((a, b) -> (a - b + MODULO) % MODULO);

        int[][] as = new int[MODULO + 1][];
        int[][] bs = new int[MODULO + 1][];

        Operation(final IntBinaryOperator op) {
            final List<List<Integer>> as = new ArrayList<>();
            final List<List<Integer>> bs = new ArrayList<>();
            for (int i = 0; i <= MODULO; i++) {
                as.add(new ArrayList<>());
                bs.add(new ArrayList<>());
            }
            for (int a = 0; a <= MODULO; a++) {
                for (int b = 0; b <= MODULO; b++) {
                    int c = a == MODULO || b == MODULO ? MODULO : op.applyAsInt(a, b);
                    as.get(c).add(a);
                    bs.get(c).add(b);
                }
            }
            for (int i = 0; i <= MODULO; i++) {
                this.as[i] = as.get(i).stream().mapToInt(a -> a).toArray();
                this.bs[i] = bs.get(i).stream().mapToInt(a -> a).toArray();
            }
        }

        public double[] apply(final double[] left, final double[] right) {
            final double[] result = new double[MODULO + 1];
            for (int i = 0; i <= MODULO; i++) {
                for (int j = 0; j < as[i].length; j++) {
                    result[i] += left[as[i][j]] * right[bs[i][j]];
                }
            }
            final double sum = stream(result).sum();
            return Arrays.stream(result).map(a -> a / sum).toArray();
        }
    }

    private double[] parseExpression() {
        double[] op = parseSum();
        while (test('m')) {
            Operation operation;
            if (test('i')) {
                operation = Operation.MIN;
                expect('n');
            } else if (test('a')) {
                operation = Operation.MAX;
                expect('x');
            } else {
                throw error("max or min expected");
            }
            op = operation.apply(op, parseSum());
        }
        return op;
    }

    private double[] parseSum() {
        double[] op = parseTerm();
        while (true) {
            Operation operation;
            if (test('+')) {
                operation = Operation.ADD;
            } else if (test('-')) {
                operation = Operation.SUB;
            } else {
                return op;
            }
            op = operation.apply(op, parseTerm());
        }
    }

    private double[] parseTerm() {
        double[] op = parseFactor();
        while (true) {
            if (test('*')) {
                op = Operation.MUL.apply(op, parseFactor());
            } else if (test('/')) {
                op = Operation.DIV.apply(op, parseFactor());
            } else {
                return op;
            }
        }
    }

    private double[] parseFactor() {
        if (test('(')) {
            double[] expression = parseExpression();
            expect(')');
            return expression;
        } else if (test('?')) {
            return RANDOM;
        } else {
            int macro = parseMacro();
            if (macros[macro] == null) {
                throw error("Undefined macro '%c'", 'a' + macro);
            }
            return macros[macro];
        }
    }

    private void expect(final char c) {
        final char found = curChar;
        if (found != c) {
            throw error("'%c' expected, '%c' found", c, found);
        }
        nextChar();
    }

    private boolean test(final char c) {
        if (curChar == c) {
            nextChar();
            return true;
        }
        return false;
    }

    private int parseMacro() {
        char macro = curChar;
        if (macro < 'a' || 'z' < macro) {
            throw error("<macro> expected, '%c' found", macro);
        }
        nextChar();
        return macro - 'a';
    }

    private void nextChar() {
        if (pos == line.length()) {
            throw error("Unexpected end of line");
        }
        curChar = line.charAt(pos++);
    }

    private Outcome error(final String format, final Object... args) {
        return new Outcome(WA, lineNo + ":" + pos + ":" + String.format(format, args));
    }
}

