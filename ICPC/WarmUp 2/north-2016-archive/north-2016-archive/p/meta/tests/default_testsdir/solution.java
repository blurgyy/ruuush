import java.util.*;
import java.io.*;

public class solution {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(System.in);
        PrintStream out = System.out;

        assert "Hello".equals(in.next());
        out.println("Hi " + in.next());

        in.close();
        out.close();
    }
}
