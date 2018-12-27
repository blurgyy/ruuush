import java.io.*;

public class Tests {
    static void writeTest(String name, String value) throws IOException {
        try (Writer writer = new FileWriter("tests/" + name)) {
            writer.write(value + "\n");
        }
    }

    public static void main(String[] args) throws IOException {
        writeTest("01", "Hello 01");
        writeTest("02", "Hello 02");
    }
}
