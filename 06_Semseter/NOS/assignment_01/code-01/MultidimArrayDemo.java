import java.util.*;

class MultidimArrayDemo {
    public static void main(String args[]) {
        // Initialized with all zeros
        int[][] tictactoe = new int[3][3];
        System.out.println(Arrays.deepToString(tictactoe));

        // A ragged array: A multi-dim array is an array of arrays, unlike in C++.
        int[][] hashtable = {{ 1, 2, 3, 4},
                             { 10, 20},
                             { 100, 200, 300}};
        System.out.println(Arrays.deepToString(hashtable));
        System.out.println("hashtable[0][3] = " + hashtable[0][3]);
        for (int[] row : hashtable)
            System.out.println("Row = " + Arrays.toString(row));
    }
}
