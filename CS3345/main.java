public class main {
    public static void main(String[] args) {
        Pair p = new Pair("this is the first thing", "big second thing");
        System.out.println("getfirst(): " + p.getfirst() + "; getsecond(): " + p.getsecond());
        System.out.println("Swapping...");
        p.swap();
        System.out.println("getfirst(): " + p.getfirst() + "; getsecond(): " + p.getsecond() + "\n");

        p = new Pair(345.33, 333.44);
        System.out.println("getfirst(): " + p.getfirst() + "; getsecond(): " + p.getsecond());
        System.out.println("Swapping...");
        p.swap();
        System.out.println("getfirst(): " + p.getfirst() + "; getsecond(): " + p.getsecond() + "\n");
    }
}

class Pair<T> {
    T first;
    T second;

    Pair(T one, T two){
        first = one;
        second = two;
    }

    public void swap(){
        T temp = second;
        second = first;
        first = temp;
    }

    public T getfirst() {
        return first;
    }

    public T getsecond() {
        return second;
    }
}
