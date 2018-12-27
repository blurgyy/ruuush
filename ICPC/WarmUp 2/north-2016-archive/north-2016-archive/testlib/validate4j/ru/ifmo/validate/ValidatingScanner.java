package ru.ifmo.validate;

import java.io.*;

public class ValidatingScanner {
    public static final String DIGITS = "0123456789";
    public static final String INTEGER = "+-" + DIGITS;
    public static final String ENGLISH_LOWER = "abcdefghijklmnopqrstuvwxyz";
    public static final String ENGLISH_UPPER = ENGLISH_LOWER.toUpperCase();
    public static final String ENGLISH_ALL   = ENGLISH_UPPER + ENGLISH_LOWER;
    public static final char NEW_LINE = 10;
    public static final char CHECKED_NEW_LINE = 13;

    private final EOLN eoln;
    private final PushbackInputStream is;
    private char ch;
    private int line = 1;
    private int column;

    private enum EOLN {
        LF {
            @Override
            public boolean isNewLine(ValidatingScanner s) {
                if (s.ch == '\r') {
                    throw s.error("Unexpected CR");
                }
                return s.ch == '\n';
            }
        },
        CR_LF {
            @Override
            public boolean isNewLine(ValidatingScanner s) {
                if (s.ch == '\n') {
                    throw s.error("LF without CR");
                }
                if (s.ch != '\r') {
                    return false;
                }
                s.ch = s.readNextChar();
                if (s.ch != '\n') {
                    throw s.error("CR without LF");
                }
                return true;
            }
        };

        static EOLN get() {
            String lineSeparator = System.lineSeparator();
            if ("\n".equals(lineSeparator)) {
                return EOLN.LF;
            } else if ("\r\n".equals(lineSeparator)) {
                return EOLN.CR_LF;
            } else {
                StringBuilder sb = new StringBuilder();
                for (char c : lineSeparator.toCharArray()) {
                    sb.append(String.format("\\u%04x", (int) c));
                }
                throw new RuntimeException("Unsupported line separator: " + sb);
            }
        }

        public abstract boolean isNewLine(ValidatingScanner s);
    }

    public ValidatingScanner(File file) {
        eoln = EOLN.get();
        try {
            is = new PushbackInputStream(new FileInputStream(file));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        nextChar();
    }

    public ValidatingScanner(InputStream inputStream) {
        eoln = EOLN.get();
        this.is = new PushbackInputStream(inputStream);
        nextChar();
    }

    private void nextChar() {
        ch = readNextChar();
        if (eoln.isNewLine(this)) {
            ch = NEW_LINE;
            line++;
            column = 1;
        } else {
            column++;
            if (ch < ' ' || ch > '\u007f') {
                throw error("Invalid character \\u%04x", (int) +ch);
            }
        }
    }

    private char readNextChar() {
        int b;
        try {
            b = is.read();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        if (b == -1) {
            throw error("Unexpected end of file");
        }
        return (char) b;
    }

    public String next(String chars, int length) {
        return next(chars, length, length);
    }

    public String next(String chars, int minLength, int maxLength) {
        skipWhitespaceBefore();
        StringBuilder sb = new StringBuilder();
        while (chars.indexOf(ch) != -1) {
            sb.append(ch);
            nextChar();
        }
        if (sb.length() < minLength) {
            throw error("String too short: " + sb);
        }
        if (sb.length() > maxLength) {
            throw error("String too long: " + sb);
        }
        expectWhitespaceAfter();
        return sb.toString();
    }

    public int nextInt(int min, int max) {
        return nextInt("value", min, max);
    }

    public int nextInt(String name, int min, int max) {
        String string = next(INTEGER, 1, 100);
        try {
            int value = Integer.parseInt(string);
            if (value < min || value > max) {
                throw error("%s out of range %d..%d: %d", name, min, max, value);
            }
            return value;
        } catch (NumberFormatException e) {
            throw error("Invalid integer %s='%s': %s", name, string, e.getMessage());
        }
    }

    public long nextLong(long min, long max) {
        String string = next(INTEGER, 1, 100);
        long value = Long.parseLong(string);
        if (value < min || value > max) {
            throw error("Value %d out of range [%d..%d]", value, min, max);
        }
        return value;
    }

    public void eoln() {
        if (ch == CHECKED_NEW_LINE) {
            nextChar();
        }
        if (ch != NEW_LINE) {
            throw error("End of line expected instead of \\u%04x", (int) ch);
        }
        ch = CHECKED_NEW_LINE;
    }

    public void close() {
        try {
            if (ch != CHECKED_NEW_LINE) {
                throw error("End of file expected instead of \\u%04x", (int) ch);
            }
            if (is.read() != -1) {
                throw error("End of file expected");
            }
            is.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public String nextWholeLine() {
        if (ch == CHECKED_NEW_LINE) {
            try {
                int next = is.read();
                if (next == -1) {
                    return null;
                }
                is.unread(next);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            nextChar();
        }
        StringBuilder sb = new StringBuilder();
        while (ch >= ' ') {
            sb.append(ch);
            nextChar();
        }
        eoln();
        return sb.toString();
    }

    public String nextLine(int minLength, int maxLength) {
        skipWhitespaceBefore();
        StringBuilder sb = new StringBuilder();
        while (ch >= ' ') {
            sb.append(ch);
            nextChar();
        }
        if (sb.length() < minLength) {
            throw error("Line too short: " + sb);
        }
        if (sb.length() > maxLength) {
            throw error("Line too long: " + sb);
        }
        eoln();
        return sb.toString();
    }

    private void skipWhitespaceBefore() {
        if (ch == NEW_LINE) {
            throw error("Unexpected end of line");
        }
        if (ch == ' ' || ch == CHECKED_NEW_LINE) {
            nextChar();
        }
    }

    private void expectWhitespaceAfter() {
        if (ch != ' ' && ch != NEW_LINE) {
            throw error("Whitespace expected, '%c' found", ch);
        }
    }

    private RuntimeException error(String format, Object... args) {
        return new RuntimeException(line + ":" + column + ": " + String.format(format, args));
    }
}
