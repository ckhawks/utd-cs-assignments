// Carter Hawks
// Project 3
// CS3345.004

// Work with hash tables by creating a hash table using linear probing.

import jdk.nashorn.internal.ir.annotations.Ignore; // make it so that the Java compiler/IDE doesn't cry

// Create a generic class called LinearProbingHashTable<K,V>.
public class LinearProbingHashTable<K, V> {

    /*
    Because Java cannot create an array of a generic class, create the
     array for the table like this:

       Entry<K,V> table[];      // declare generic
       table = new Entry[size]; // create as non-generic

     Note that this will generate a warning message when compiled.
     */

    int size;
    int entries = 0;
    Entry<K, V> table[]; // declare generic

    private static final int DEFAULT_TABLE_SIZE = 8;

    // constructors
    public LinearProbingHashTable(){
        this(DEFAULT_TABLE_SIZE);
    }

    public LinearProbingHashTable(int table_size){
        size = table_size;
        table = new Entry[size]; // create as non-generic
    }


    // It should contain a private static class, Entry<K,V>, which contains both K and V.
    private static class Entry<K, V> {
        K key;                      // the key
        V value;                    // the data or value
        public boolean isActive;    // false if marked deleted

        public Entry(K k, V v){
            key = k;
            value = v;
            isActive = true;
        }

    }

    /*
    Your class should have the following methods.  The methods should
     all operate on the object making the call (none are static).

     Perform checking of the parameters and throw exceptions where
     appropriate.

     You may use code from the textbook, but all other code must be
     your own.
     */

    // inserts entry, rehashes if half full,
    //         can re-use deleted entries, throws
    //         exception if key is null, returns
    //         true if inserted, false if duplicate.
    public boolean insert(K key, V value) throws Exception {

        // check if key is null
        if(key == null){
            throw new Exception("Key cannot be null");
        }

        // get hash value of key
        int hash = getHashValue(key);
        int startHash = hash;
        boolean inserted = false;
        do {

            // check if hash slot is not filled
            if(table[hash] == null){
                table[hash] = new Entry<>(key, value);
                entries++;
                inserted = true;
                break;
            }

            // check if key is duplicate
            if(table[hash].key == key){
                // key is duplicate
                inserted = false;
                break;
            }

            // check if hash slot is filled but marked as deleted
            if(table[hash] != null && !table[hash].isActive){
                table[hash] = new Entry<>(key, value);
                // do not increment entries as we replaced a different value
                inserted = true;
                break;
            }

            // linear probe forward
            hash = (hash + 1) % size;
        }
        while(hash != startHash);

        // check if necessary for rehash
        if(entries >= size / 2){
            rehash();
        }

        return inserted;
    }


    // returns value for key, or null if not found
    public V find(K key){
        // get hash value of key
        int hash = getHashValue(key);

        // start at hash and linear probe past if necessary
        while (table[hash] != null) {

            // check if key matches
            if (table[hash].key == key) {
                return table[hash].value;
            }

            hash = (hash + 1) % size; // linear probe on to the next hash

            if(hash == getHashValue(key)){
                return null;
            }
        }

        // _shouldn't_ reach this statement
        return null;
    }


    // marks the entry deleted but leaves it there,
    //    returns true if deleted, false if not found
    public boolean delete(K key){
        // get hash value of key
        int hash = getHashValue(key);
        while (table[hash] != null) {

            // check if key matches
            if (table[hash].key == key){

                // mark key deleted
                table[hash].isActive = false;
                return true;
            }

            hash = (hash + 1) % size;

            // breaking condition: went through all possible hash values
            if(hash == getHashValue(key)){
                return false;
            }
        }

        // it really should not reach this one
        return false;
    }


    // doubles the table size, hashes everything to
    // the new table, omitting items marked deleted
    private void rehash(){
        // set up new table with doubled table size
        Entry<K, V> workingTable[];
        workingTable = new Entry[size * 2];

        // hash everything to new table
        for(int i = 0; i < size; i++){
            if(table[i] != null){

                // omit inactive items
                if(table[i].isActive){
                    int newHash = table[i].key.hashCode() % (size * 2);
                    boolean inserted = false;

                    do {
                        if(workingTable[newHash] == null){
                            workingTable[newHash] = new Entry(table[i].key, table[i].value);
                            inserted = true;
                            break;
                        }

                        // linear probe forward if space taken
                        newHash = (newHash + 1) % (size * 2);
                    }
                    while(!inserted);
                }

            }

        }

        // last thing
        // redefine class variables to new table
        size = size * 2;
        table = workingTable;
    }


    // returns the hash value for the given key.
    //    (this is the value before probing occurs)
    public int getHashValue(K key){
        return key.hashCode() % size;
    }


    // returns the location (index) for the given key,
    //    or -1 if not found.
    //            (this is the value after probing occurs)
    public int getLocation(K key){
        // get hash value of key
        int hash = getHashValue(key);
        int startingHash = hash;


        while(table[hash] != null){

            // check if key at hash matches provided key
            if(table[hash].key == key){
                return hash;
            }

            hash = (hash + 1) % size;

            // check if we got back to the start
            if(hash == startingHash){
                return -1;
            }
        }

        return -1;
    }


    /*
    returns a formatted string of the hash table,
          where k, v is the key and value at this location:
               0  k, v
               1
               2  k, v   deleted
               ...
     */
    public String toString(){
        String output = "";
        for(int i = 0; i < size; i++){
            Entry<K,V> e = table[i];

            if(e == null) {
                output = output + i + " empty";
            } else {
                output = output + (e.isActive
                        ? i + " " + e.key + " " + e.value
                        : i + " " + e.key + " " + e.value + " deleted");
                // super sick big brain ternary operator usage right lol
            }
            output = output + "\n";
        }
        return output;
    }


    // demonstrate each of your methods
    public static void main(String args[]) throws Exception {
        LinearProbingHashTable t = new LinearProbingHashTable<>();
        System.out.println("Printing table\n" + t.toString());
        System.out.println("Inserting `14`: " + t.insert(14, 4) + " (expected: true)");
        System.out.println(t.toString());
        System.out.println("Inserting `14`: " + t.insert(14, 4) + " (expected: false)");
        System.out.println(t.toString());
        System.out.println("Inserting `22`: " + t.insert(22, 65) + " (expected: true)");
        System.out.println(t.toString());
        System.out.println("Finding value of `22`: " + t.find(22) + " (expected: 65)");
        System.out.println("Inserting `23`: " + t.insert(23, 43) + " (expected: true)");
        System.out.println(t.toString());
        System.out.println("Finding location of `22`: " + t.getLocation(22) + " (expected: 7)");
        System.out.println("Deleting `22`: " + t.delete(22) + " (expected: true)");
        System.out.println(t.toString());
        System.out.println("Inserting `30`: " + t.insert(30, 8) + " (expected: true)");
        System.out.println("Inserting `30`: " + t.insert(10, 2) + " (expected: true, will rehash)"); // this causes a rehash
        System.out.println(t.toString());
    }

}
