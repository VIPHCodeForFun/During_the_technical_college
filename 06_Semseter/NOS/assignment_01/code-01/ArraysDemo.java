import java.util.*;                              // We need java.util.Arrays

class ArraysDemo {
    public static void main(String args[]) {
        int[] a = new int[6];                    // Uninitialized
        for (int i=0; i < a.length; ++i)         // a.length gives the array size
            a[i] = i * i;
        System.out.println(Arrays.toString(a));

        int[] b = {0, 1, 4, 9, 16, 25};
        System.out.println(Arrays.equals(a, b));

        int sum = 0;
        for (int elem : b)                       // Java 5 has a foreach loop, as C++11
            sum += elem;
        System.out.println(sum);
    }
}
