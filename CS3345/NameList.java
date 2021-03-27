// Carter Hawks
// CS3345.004
// Project 1 - NameList

public class NameList {

    private Node entryNode;

    private class Node {

        private Node(String v, Node n){
            value = v;
            next = n;
        }

        private Node(String v){
            value = v;
        }

        public String value;
        public Node next = null;
    }

    // Suppose the names "Bob", "Dan", and "Ben", are added, the result is:
    //
    //                -----     -----     -----     -----     -----
    //       head -->|  B  |-->| Ben |-->| Bob |-->|  D  |-->| Dan |--
    //                -----     -----     -----     -----     -----   |
    //                                                               ---
    //                                                                -
    //
    //
    //
    //   If the names "Deb" and "Sarah" are added, it looks like this:
    //
    //                -----     -----     -----     -----     -----     -----      -----     -----
    //       head -->|  B  |-->| Ben |-->| Bob |-->|  D  |-->| Dan |-->| Deb |--> |  S  |-->|Sarah|--
    //                -----     -----     -----     -----     -----     -----      -----     -----   |
    //                                                                                              ---
    //                                                                                               -
    //
    //   If "Deb" and "Sarah" are deleted, the list should look like the first list again.

    // Create a Java class called NameList (not generic) that stores names and implements the
    //   structure shown above.
    //
    //   Note that the names are kept in sorted order.  Letter nodes are always uppercase.
    //   Names may begin with a lowercase letter, but ordering is case insensitive.  For example,
    //   if Dewy, Donna, Deb, deWitt, Dan are added, they would all be placed in the D list in
    //   the order Dan, Deb, deWitt, Dewy, Donna.
    //
    //   You may *not* use Java's LinkedList class.  You should create your own nodes and
    //   link them together as shown in the illustration.

    // Adds a new name.  Names must be at least 2 characters long.  Adds the letter node if not already present.
    public void add(String name){

        // check for name length requirement
        if(name.length() < 2){
            System.out.println("Names must be at least 2 characters long.");
            return;
        }

        // search for letter node
        String letter = name.substring(0, 1);
        //System.out.println(letter);

        Node n = new Node(name);
        if(entryNode == null){
            // NameList is empty
            addNodeAfter(null, n, null, false);
            /*System.out.println("NameList is empty, adding " + name + " at entryNode.");
            Node letterNode = new Node(letter);
            entryNode = letterNode;
            letterNode.next = n;*/

        } else {
            // NameList has contents
            Node currentNode = entryNode;
            Node previousNode = null;
            boolean hasLetter = false;
            while(currentNode != null){

                // print current status
                if(previousNode != null){
                    //System.out.println("Adding \"" + name + "\", currently at " + currentNode.value + ", previous: " + previousNode.value);
                } else {
                    //System.out.println("Adding \"" + name + "\", currently at " + currentNode.value);
                }

                // check if we have passed the corresponding letter
                if(currentNode.value.equalsIgnoreCase(name.substring(0, 1))){
                    hasLetter = true;
                    //System.out.println("Has letter");
                }

                // check if name should fit here
                // System.out.println("Baaa".compareTo("Ban")); = -13
                if(currentNode.value.toLowerCase().compareTo(name.toLowerCase()) < 0){
                    // current < name

                    if(currentNode.next == null){
                        // nothing to move forward to
                        addNodeAfter(currentNode, n, null, hasLetter);
                        break;
                    } else {
                        // move forward
                        previousNode = currentNode;
                        currentNode = currentNode.next; // move to next
                    }


                } else {
                    // current > name
                    // needs to place after previous
                    addNodeAfter(previousNode, n, currentNode, hasLetter);
                    break;
                }

                // did not find
                // currentNode = currentNode.next; // proceed to next
            }


        }

    }

    // places newNode between previousNode and followingNode
    //   adds letter node if doesn't exist yet
    void addNodeAfter(Node previousNode, Node newNode, Node followingNode, boolean hasLetter){
        //System.out.println("addNodeAftering node " + newNode.value);

        // this will happen for every case
        if(followingNode != null){
            newNode.next = followingNode;
        }

        if(hasLetter){

            if(previousNode == null){ // this is impossible
                System.out.println("IMPOSSIBLE CASE");
                entryNode = newNode;
            } else { // should always be true if hasLetter
                previousNode.next = newNode;
            }

        } else {

            // does not have an existing letter node
            Node letterNode = new Node(newNode.value.toUpperCase().substring(0, 1));
            letterNode.next = newNode;


            if(previousNode == null){
                // if there is no previous node, we set entryNode to the new letter
                entryNode = letterNode;
            } else {
                previousNode.next = letterNode;
            }
        }
    }

    // Removes a name.  If the name is the last one for a letter, the letter
    //             node should also be removed.
    public void remove(String name){

        // Check NameList not empty
        if(entryNode != null){
            Node currentNode = entryNode;
            Node previousNode = null;
            boolean removeLetter = false;
            while(currentNode != null) {
                //System.out.println("Removing \"" + name + "\", current node: " + currentNode.value);
                if (currentNode.value.equalsIgnoreCase(name)) {
                    int count = getNumOfLetter(name.substring(0, 1));
                    if(count == 1){
                        // remove letter too
                        removeLetter = true;
                    }

                    if (previousNode == null) {
                        // beginning
                        if (currentNode.next == null) {
                            // only node is the one being removed
                            entryNode = null;
                        } else {
                            // set 2 to 1
                            entryNode = currentNode.next;
                        }
                    } else {
                        if (currentNode.next == null) {
                            previousNode.next = null;
                        } else {
                            previousNode.next = currentNode.next;
                        }
                    }

                    // remove letter if we need to
                    if(removeLetter){
                        remove(name.substring(0, 1));
                    }

                    break;
                } else {
                    previousNode = currentNode;
                    currentNode = currentNode.next;
                }
            }
        }
    }

    int getNumOfLetter(String letter){
        int count = 0;
        // Check NameList not empty
        if(entryNode != null){
            Node currentNode = entryNode;
            Node previousNode = null;
            while(currentNode != null) {
                if(currentNode.value.substring(0, 1).equalsIgnoreCase(letter) && currentNode.value.length() > 1){
                    count++;
                }
                // proceed to next node
                previousNode = currentNode;
                currentNode = currentNode.next;

            }
        }
        return count;
    }


    // Removes a letter and all names for that letter.
    public void removeLetter(String letter){
        if(letter.length() != 1){
            System.out.println("Provided letter must be 1 character long.");
            return;
        }

        letter = letter.toUpperCase();
        Node startLink = null;
        Node endLink = null;
        if(entryNode != null){
            Node currentNode = entryNode;
            Node previousNode = null;
            while(currentNode != null) {

                // locate start (node before letter)
                // "C".substring(0, 1).equalsIgnoreCase("C") == false?
                if(currentNode.value.substring(0, 1).equalsIgnoreCase(letter) && startLink == null){
                    startLink = previousNode;
                }

                // locate end
                if(!currentNode.value.substring(0, 1).equalsIgnoreCase(letter) && endLink == null && startLink != null){
                    endLink = currentNode;
                }

                // proceed to next node
                previousNode = currentNode;
                currentNode = currentNode.next;
            }
            if(startLink == null){
                if(endLink == null){
                    entryNode = null;
                } else {
                    entryNode = endLink;
                }
            } else {
                if(endLink == null){
                    startLink.next = null;
                } else {
                    startLink.next = endLink;
                }
            }


        }
        // find letter node
        //    find node before letter node
        // find next node that isn't part of that letter
        // set node before letter node.next to next node that isn't part of that letter
    }


    // Finds a name by traversing the nodes, returns a boolean.
    public boolean find(String name){

        // check NameList not empty
        if(entryNode != null){
            Node currentNode = entryNode;
            Node previousNode = null;
            while(currentNode != null){
                //System.out.println("Searching for \"" + name + "\", current node: " + currentNode.value);
                if(currentNode.value.equalsIgnoreCase(name)){
                    return true;
                } else {
                    // proceed to next node
                    previousNode = currentNode;
                    currentNode = currentNode.next;

                }
            }
        }

        return false;
    }

    // Returns a string of the list formatted as shown below using the first list above as an example:
    //       B
    //         Ben
    //         Bob
    //       D
    //         Dan
    @Override
    public String toString() {
        String output = "";

        if (entryNode != null) {
            Node currentNode = entryNode;
            Node previousNode = null;
            while (currentNode != null) {
                //System.out.println("Working on printing " + currentNode.value);
                // append node value to output

                if (currentNode.value.length() > 1) { // used to indent based on value length (for letters vs names)
                    // not letter
                    output = output + "\n  " + currentNode.value;
                } else {
                    // letter
                    output = output + "\n" + currentNode.value;
                }


                // proceed to next node
                previousNode = currentNode;
                currentNode = currentNode.next;

            }
        }

        return output;
    }

    // Demonstrates the methods of your NameList class
    public static void main(String[] args) {
        NameList nL = new NameList();

        System.out.println(nL.toString());
        //nL.add("a");
        nL.add("Deb");
        System.out.println(nL.toString());
        nL.add("Ben");
        System.out.println(nL.toString());
        nL.add("Bob");
        System.out.println(nL.toString());
        System.out.println("Number of B's: " + nL.getNumOfLetter("B") + " (expected: 2)");
        nL.add("Dan");
        System.out.println(nL.toString());
        System.out.println("Number of D's: " + nL.getNumOfLetter("D") + " (expected: 2)");
        System.out.println("Dan found: " + nL.find("Dan") + " (expected: true)");
        System.out.println("Sarah found: " + nL.find("Sarah") + " (expected: false)");
        System.out.println("S found: " + nL.find("S") + " (expected: false)");
        System.out.println("B found: " + nL.find("B") + " (expected: true)");
        nL.add("Sarah");
        System.out.println(nL.toString());
        System.out.println("Number of S's: " + nL.getNumOfLetter("S") + " (expected: 1)");
        nL.remove("Deb");
        System.out.println(nL.toString());
        nL.remove("Sarah");
        System.out.println(nL.toString());
        nL.add("Carter");
        nL.add("Chase");
        nL.add("Connor");
        System.out.println(nL.toString());
        nL.removeLetter("C");
        System.out.println(nL.toString());


    }
}

