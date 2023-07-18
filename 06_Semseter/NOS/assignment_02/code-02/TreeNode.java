import java.util.Objects;

class TreeNode implements Cloneable {
    public String name;
    public TreeNode left;
    public TreeNode right;

    TreeNode(String name) {
        this(name, null, null);
    }

    TreeNode(String name, TreeNode left, TreeNode right) {
        this.name = name;
        this.left = left;
        this.right = right;
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        TreeNode obj = (TreeNode) super.clone();

        if (left != null)
            obj.left = (TreeNode) left.clone();
        if (left != null)
            obj.right = (TreeNode) right.clone();
        return obj;
    }

    @Override
    public String toString() {
        return "[" + name + ": " +  Objects.toString(left, "[]") + ", " + Objects.toString(right, "[]") + "]";
    }

    public static void main(String args[]) throws CloneNotSupportedException {
        TreeNode orig = new TreeNode("root", new TreeNode("left"), new TreeNode("right"));
        TreeNode cpy = (TreeNode) orig.clone();

        cpy.name = "root2";
        cpy.left.name = "left2";
        cpy.right.name = "right2";

        System.out.println("orig = " + orig.toString());
        System.out.println("cpy = " + cpy.toString());
    }
}
