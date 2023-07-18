import java.util.Scanner;

public class HangmanUserInterface {

    Scanner reader;
    HangmanLogic hangman;

    public HangmanUserInterface() {
        // Constructor
        this.reader = new Scanner(System.in);  // HangmanUserInterface "has-a" Scanner
        this.hangman = new HangmanLogic();  // HangmanUserInterface "has-a" HangmanLogic
    }

    public boolean gameWon() {
        // TODO return wheter the game is won or not
        return false;
    }

    public boolean gameLost() {
        // TODO return wheter the game is lost or not
        return false;
    }

    public void run() {
        System.out.println("  _    _                                         ");
        System.out.println(" | |  | |                                        ");
        System.out.println(" | |__| | __ _ _ __   __ _ _ __ ___   __ _ _ __  ");
        System.out.println(" |  __  |/ _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\ ");
        System.out.println(" | |  | | (_| | | | | (_| | | | | | | (_| | | | |");
        System.out.println(" |_|  |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|");
        System.out.println("                      __/ |                      ");
        System.out.println("                     |___/                       ");
        System.out.println("");
        printMenu();
        System.out.println("");

        while (!gameWon() && !gameLost()) {  // TODO while the game is not over
            System.out.println("Type a command:");
            String inputer = reader.nextLine();

            /*  TODO
                check if the read line corresponds to a command stated in ``printMenu``:
                    - quit:     terminate the program
                    - status:   print the number of guesses and the current approach
                    - letter:   use the letter as a guess
                    - _empty_:  print the menu
            */
        }
    }


    public void hangmanImage(int count) {
        if (count == 1) {
            System.out.println();
            System.out.println();
            System.out.println();
            System.out.println();
            System.out.println("___|___");
            System.out.println();
        }
        if (count == 2) {
            System.out.println("   |");
            System.out.println("   |");
            System.out.println("   |");
            System.out.println("   |");
            System.out.println("   |");
            System.out.println("   |");
            System.out.println("   |");
            System.out.println("___|___");
        }
        if (count == 3) {
            System.out.println("   ____________");
            System.out.println("   |");
            System.out.println("   |");
            System.out.println("   |");
            System.out.println("   |");
            System.out.println("   |");
            System.out.println("   |");
            System.out.println("   | ");
            System.out.println("___|___");
        }
        if (count == 4) {
            System.out.println("   ____________");
            System.out.println("   |          _|_");
            System.out.println("   |         /   \\");
            System.out.println("   |        |     |");
            System.out.println("   |         \\_ _/");
            System.out.println("   |");
            System.out.println("   |");
            System.out.println("   |");
            System.out.println("___|___");
        }
        if (count == 5) {
            System.out.println("   ____________");
            System.out.println("   |          _|_");
            System.out.println("   |         /   \\");
            System.out.println("   |        |     |");
            System.out.println("   |         \\_ _/");
            System.out.println("   |           |");
            System.out.println("   |           |");
            System.out.println("   |");
            System.out.println("___|___");
        }
        if (count == 6) {
            System.out.println("   ____________");
            System.out.println("   |          _|_");
            System.out.println("   |         /   \\");
            System.out.println("   |        |     |");
            System.out.println("   |         \\_ _/");
            System.out.println("   |           |");
            System.out.println("   |           |");
            System.out.println("   |          / \\ ");
            System.out.println("___|___      /   \\");
        }
        if (count == 7) {
            System.out.println("   ____________");
            System.out.println("   |          _|_");
            System.out.println("   |         /   \\");
            System.out.println("   |        |     |");
            System.out.println("   |         \\_ _/");
            System.out.println("   |          _|_");
            System.out.println("   |         / | \\");
            System.out.println("   |          / \\ ");
            System.out.println("___|___      /   \\");
            System.out.println("GAME OVER! The word was " + hangman.getWord());
        }
    }

    public static void printMenu() {
        System.out.println("* menu *");
        System.out.println("quit:\tquits the game");
        System.out.println("status:\tprints the game status");
        System.out.println("a single letter uses the letter as a guess");
        System.out.println("an empty line prints this menu");
    }
}