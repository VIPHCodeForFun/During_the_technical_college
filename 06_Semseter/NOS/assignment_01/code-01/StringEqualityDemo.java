class StringEqualityDemo {
    public static void main(String args[]) {
        String str1 = "Hello";
        String str2 = str1 + "";

        System.out.println(str1 != str2);         // Not identical, different instances
        System.out.println(str1.equals(str2));    // But two equal instances
    }
}
