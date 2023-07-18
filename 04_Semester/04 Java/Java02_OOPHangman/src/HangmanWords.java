import java.io.FileInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class HangmanWords {
    private final List<String> words = new ArrayList<>();

    public HangmanWords(String file) {
        // Constructor that reads a textfile ``file`` and stores its data in an ArrayList
        try {
            FileInputStream fis = new FileInputStream(file);
            Scanner sc = new Scanner(fis);
            // TODO iterate over all lines and ``words.add(...)`` it to the ArrayList
            sc.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public String getRandomWord() {
        // TODO return a random word from ``words``
        return "foobar";
    }
}
