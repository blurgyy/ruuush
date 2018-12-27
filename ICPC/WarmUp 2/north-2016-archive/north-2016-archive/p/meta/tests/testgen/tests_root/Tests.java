import java.io.*;

public class Tests {
    static void writeTest(String name, String value) throws IOException {
        try (PrintWriter writer = new PrintWriter(new FileWriter("tests/" + name))) {
            writer.println(value);
        }
    }

    public static void main(String[] args) throws IOException {
        writeTest("01", "Hello 01");
        writeTest("02", "Hello 02");
    }
}
