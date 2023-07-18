class EmptyNullDemo {
    public static void main(String args[]) {
        String notmuch = "";
        String notatall = null;

        System.out.println(notmuch.length());    // 0
        System.out.println(notatall == null);    // true
        //System.out.println(notatall.length()); // Runtime error: NullPointerException

        // Lazy evaluation: As notatall != null is already false the second
        // operand of && is not evaluated. Similar with ||.
        System.out.println(notatall != null && notatall.length() > 0);   // false
        System.out.println(notatall == null || notatall.length() == 0);  // true
    }
}
