import java.util.Scanner;

public class HangmanLogic {


    private String word;
    private String currentApproach;
    private int guesses = 0;


    public void setWord(String word) {
        // TODO create setter for this.word
    }

    public String getWord() {
        // TODO create getter for this.word
        return "";
    }

    public int getGuesses() {
        // TODO return guesses
        return 0;
    }

    public void initCurrentApproach(String word) {
        // TODO replace all letters in ``word`` with "-" and store it in currentApproach
    }

    public void setCurrentApproach(String word) {
        currentApproach = word;
    }

    public String getCurrentApproach() {
        return currentApproach;
    }

    public HangmanLogic() {
        // Constructor
        HangmanWords words = new HangmanWords("./hard_words.txt");  // HangmanLogic "has-a" HangmanWords-object
        String word = words.getRandomWord();
        setWord(word);
        initCurrentApproach(word);
    }

    public void printStatus() {
        System.out.println(currentApproach);
    }

    public void guessChar(char guess) {
        StringBuilder newApproach = new StringBuilder();

        /*  TODO
            build a new String with the provided guess using the ``currentApproach``
            don't forget to increment the guesses if the letter was not found in the ``word``
         */

        setCurrentApproach(newApproach.toString());
    }

}
