/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem C. CodeCoder vs TopForces                              */
/*                                                                */
/* Original idea         Egor Kulikov                             */
/* Problem statement     Egor Kulikov                             */
/* Test set              Egor Kulikov                             */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Georgiy Korneev                          */
/******************************************************************/

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class codecoder_gk {
    private static Scanner in;
    private static PrintWriter out;

    static class Person {
        final int s1;
        final int s2;
        int i1;
        int i2;
        int answer;

        Person(final int s1, final int s2) {
            this.s1 = s1;
            this.s2 = s2;
        }
    }

    private static class Solution {
        void run() {
            final int n = in.nextInt();
            final List<Person> persons = IntStream.range(0, n)
                    .mapToObj(i -> new Person(in.nextInt(), in.nextInt()))
                    .collect(Collectors.toList());
            final List<Person> sortedPersons1 = persons.stream()
                    .sorted(Comparator.comparingInt(p -> p.s1))
                    .collect(Collectors.toList());
            IntStream.range(0, sortedPersons1.size()).forEach(i -> sortedPersons1.get(i).i1 = i);

            final List<Person> sortedPersons2 = persons.stream()
                    .sorted(Comparator.comparingInt(p -> p.s2))
                    .collect(Collectors.toList());
            IntStream.range(0, sortedPersons2.size()).forEach(i -> sortedPersons2.get(i).i2 = i);

            int tail = 0;
            for (Person person : sortedPersons1) {
                int head = person.i2;
                while (tail <= head) {
                    head = Math.max(head, sortedPersons1.get(tail++).i2);
                }
                person.answer = tail - 1;
            }
            persons.forEach(person -> out.println(person.answer));
        }
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("codecoder.in"));
        out = new PrintWriter("codecoder.out");

        new Solution().run();

        in.close();
        out.close();
    }

    static class Scanner {
        final BufferedReader reader;
        StringTokenizer tokenizer = new StringTokenizer("");

        Scanner(File file) throws FileNotFoundException {
            reader = new BufferedReader(new FileReader(file));
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        String next() {
            while (!tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new AssertionError();
                }
            }
            return tokenizer.nextToken();
        }

        void close() {
        }
    }
}

