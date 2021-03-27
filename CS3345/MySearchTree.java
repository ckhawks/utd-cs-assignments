// Carter Hawks - ckh170000
// CS3345.004 Project 2
// Binary Search Tree

public class MySearchTree<T extends Comparable<T>> {

    Node<T> root;

    // Create a class called MySearchTree.  MySearchTree will implement a binary
    //   search tree.  MySearchTree will be a generic class storing a value of the
    //   generic type.
    //
    //   It should have the following methods.  The methods should
    //   all operate on the object making the call (none are static).
    public MySearchTree(){
        this.root = null;
    }


    // Adds a node to the tree containing the passed value.
    public void add(T value){
        root = addRecursive(value, root);
    }

    // helper method for add()
    private Node<T> addRecursive(T value, Node<T> n){
        if(n == null){
            return new Node<T>(value, null, null);
        }

        int comparison = value.compareTo(n.value);

        if(comparison < 0){
            n.left = addRecursive(value, n.left);
        } else if(comparison > 0){
            n.right = addRecursive(value, n.right);
        } else {
            // node is duplicate, do nothing.
        }
        return n;
    }


    // Returns true if the value passed is in the tree.
    public boolean find(T value){
        return findRecursive(value, root);
    }

    // helper method for find() method
    private boolean findRecursive(T value, Node<T> n){

        // check if this node exists
        if(n == null){
            return false;
        }

        int comparison = value.compareTo(n.value);

        if(comparison < 0){
            return findRecursive(value, n.left);
        } else if(comparison > 0){
            return findRecursive(value, n.right);
        } else { // comparison == 0
            // found match
            return true;
        }
    }


    // Returns the count of all of the leaves in the tree.
    public int leafCount(){
        return leafCountRecursive(root);
    }

    // helper method for leafCount()
    private int leafCountRecursive(Node<T> n){
        if(n == null){
            return 0;
        } else {
            return 1 + leafCountRecursive(n.left) + leafCountRecursive(n.right);
        }
    }


    // Returns the count of all of the parents in the tree.
    public int parentCount(){
        return parentCountRecursive(root);
    }

    // helper method for parentCount()
    private int parentCountRecursive(Node<T> n){
        if(n == null){
            return 0;
        }

        // check if has at least one child
        if(n.left == null && n.right == null){ // if has NO child, return 0
            return 0;
        }

        return 1 + parentCountRecursive(n.left) + parentCountRecursive(n.right);
    }


    // Returns the height of the tree.
    public int height(){
        return heightRecursive(root);
    }

    // helper method for height()
    private int heightRecursive(Node<T> n) {
        if (n == null) {
            return 0;
        }

        return 1 + Math.max(heightRecursive(n.left), heightRecursive(n.right));
    }


    // Returns true if the tree is a perfect tree.
    //   (A perfect tree is filled at every level).
    public boolean isPerfect(){
        int height = height() - 1; // height() uses recursion
        int leafs = leafCount(); // leafCount() uses recursion
        return Math.pow(2, height + 1) - 1 == leafs;
    }


    // Returns the ancestor values of the passed value.
    public String ancestors(T value){ // NOT SURE OF THIS RETURN TYPE
        // find(T value); going to have to reimplement this
        Node<T> n = ancestorsFindNodeRecursive(value, root);

        return ancestorsOfNode(n);
    }

    private String ancestorsOfNode(Node<T> n){
        String output = "";

        output = output + "ancestors of node " + n.value + "\n";

        if(n.left != null){
            output = output + "left: " + n.left.value + "\n";
        }

        if(n.right != null){
            output = output + "right: " + n.right.value + "\n";
        }

        return output;
    }

    // helper method for ancestors() method
    private Node<T> ancestorsFindNodeRecursive(T value, Node<T> n){

        // check if this node exists
        if(n == null){
            return null;
        }

        int comparison = value.compareTo(n.value);

        if(comparison < 0){
            return ancestorsFindNodeRecursive(value, n.left);
        } else if(comparison > 0){
            return ancestorsFindNodeRecursive(value, n.right);
        } else { // comparison == 0
            // found match
            return n;
        }
    }


    // Prints node values using an inorder traversal.
    public void inOrderPrint(){
        inOrder(root);
    }

    // helper method for inOrderPrint()
    private void inOrder(Node<T> n){
        if(n == null){
            return;
        }

        inOrder(n.left);
        System.out.printf("%s ", n.value);
        inOrder(n.right);
    }


    // Prints node values using a preorder traversal.
    public void preOrderPrint(){
        preOrder(root);
    }

    // helper method for preOrderPrint()
    private void preOrder(Node<T> n){
        if(n == null){
            return;
        }

        System.out.printf("%s ", n.value);
        preOrder(n.left);
        preOrder(n.right);
    }

    // just for the fun of it
    public void postOrderPrint(){
        postOrder(root);
    }

    // helper method for postOrderPrint()
    private void postOrder(Node<T> n){
        if(n == null){
            return;
        }

        postOrder(n.left);
        postOrder(n.right);
        System.out.printf("%s ", n.value);
    }

    // Demonstrates all of the above methods.
    public static void main(String[] args) {
        MySearchTree mst = new MySearchTree();

        /*
            The BST should look like this after runtime.
                      4
                  2       6
                1   3   5   7

         */

        // demonstrating add(), height()
        mst.add(4);
        System.out.println("height: " + mst.height() + " (expected: 1)");
        mst.add(2);
        System.out.println("height: " + mst.height() + " (expected: 2)");
        mst.add(6);

        // demonstrating leafCount(), isPerfect(), parentCount()
        System.out.println("leaf count: " + mst.leafCount() + " (expected: 3)");
        System.out.println("isPerfect: " + mst.isPerfect() + " (expected: true)");
        System.out.println("parentCount: " + mst.parentCount() + " (expected: 1)");
        System.out.println("height: " + mst.height() + " (expected: 2)");
        mst.add(1);
        System.out.println("isPerfect: " + mst.isPerfect() + " (expected: false)");
        mst.add(3);
        mst.add(5);
        mst.add(7);
        System.out.println("leaf count: " + mst.leafCount() + " (expected: 7)");
        System.out.println("isPerfect: " + mst.isPerfect() + " (expected: true)");
        System.out.println("parentCount: " + mst.parentCount() + " (expected: 3)");
        System.out.println("height: " + mst.height() + " (expected: 3)");

        // demonstrating preOrderPrint(), inOrderPrint() ( bonus: postOrderPrint() )
        System.out.print("preorder: ");
        mst.preOrderPrint();
        System.out.println();
        System.out.print("inorder: ");
        mst.inOrderPrint();
        System.out.println();
        /*System.out.print("postorder: ");
        mst.postOrderPrint();
        System.out.println();*/

        // demonstrating find()
        System.out.println("Node '3' found: " + mst.find(3) + " (expected: true)");
        System.out.println("Node '8' found: " + mst.find(8) + " (expected: false)");

        // demonstrating ancestors()
        System.out.println("Ancestors of node '4': " + mst.ancestors(4) + " (expected: left: 2, right: 6)");
        System.out.println("Ancestors of node '6': " + mst.ancestors(6) + " (expected: left: 5, right: 7)");
    }
}

class Node<T extends Comparable<T>> {
    T value;
    Node<T> left;
    Node<T> right;

    public Node(T value){
        this.value = value;
        this.left = null;
        this.right = null;
    }

    public Node(T value, Node<T> left, Node<T> right) {
        this.value = value;
        this.left = left;
        this.right = right;
    }
}
