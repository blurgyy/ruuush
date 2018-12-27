import java.io.*;

public class doall {
    static void writeTest(String name, String value) throws IOException {
        try (PrintWriter writer = new PrintWriter(new FileWriter(name))) {
            writer.println(value);
        }
    }

    public static void main(String[] args) throws IOException {
        writeTest("01", "Hello 01");
        writeTest("02", "Hello 02");
    }
}
