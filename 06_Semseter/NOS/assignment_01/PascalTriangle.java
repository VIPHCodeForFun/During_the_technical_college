
/* Philipp Vidmar 
 * [1]  https://en.wikipedia.org/wiki/Pascal%27s_triangle
*/
import java.util.Scanner;

/** Expand array dynamically at runtime */
public class PascalTriangle {
    public static int[][] addRow(int[][] array, int[] newRow) {
        int[][] newArray = new int[array.length + 1][];
        for (int i = 0; i < array.length; i++) {
            newArray[i] = array[i];
        }
        newArray[array.length] = newRow;
        return newArray;
    }

    public static void main(String args[]) {
        // 2D array for triangle
        int[][] triangle = new int[][] {};

        /* Catch Imput */
        System.out.println("How many rows?");
        Scanner scanner = new Scanner(System.in);
        int numberOfRows = 5;
        try {
            numberOfRows = scanner.nextInt();
        } catch (Exception ex) {
            System.out.println(
                    "Oopsie daisy, looks like the input took a wrong turn somewhere - did we take a left at Albuquerque or what?");
            ex.printStackTrace(System.out);
            System.out.println(
                    "Looks like we've got a case of the input row blues - we need 5 of 'em to keep this show on the road!");
        }
        scanner.close();

        /* Calculate Pascaltriangle */
        for (int row = 1; row < numberOfRows + 1; row++) {
            int[] newRow = new int[row];
            newRow[0] = 1; // First element always 1
            newRow[newRow.length - 1] = 1; // Last element always 1

            for (int pos = 1; pos < newRow.length - 1; pos++) {
                int previousRow = row - 2;
                newRow[pos] = triangle[previousRow][pos - 1] + triangle[previousRow][pos];
            }
            triangle = addRow(triangle, newRow);
        }

        /* Console Output Pascaltriangle */
        int remainingRows = triangle.length;
        for (int row = 0; row < triangle.length; row++) {
            System.out.printf("[%2d]", row);
            for (int space = 0; space < remainingRows; space++) {
                System.out.print("   ");
            }
            remainingRows--;
            for (int pos = 0; pos < triangle[row].length; pos++) {
                // System.out.print(triangle[row][j] + " ");
                System.out.printf("%6d", triangle[row][pos]);
            }
            System.out.println();
        }
    }
}
