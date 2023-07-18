import java.util.Arrays;

public class Function {
    public static int[] addInt(int[] array, int element) {
        array = Arrays.copyOf(array, array.length + 1);
        array[array.length - 1] = element;
        return array;
    }
}
