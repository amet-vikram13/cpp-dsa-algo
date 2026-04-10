class SomeClass {

    int val;

    SomeClass(int val) {
        this.val = val;
    }
}

public class JavaMemory {

    // Java is strictly pass-by-value
    // 1. first we are passing a reference and then changing the object value
    // pointed by that reference.
    // 2. second we are destroying the reference copy but the original object remains unchanged
    // 3.
    static void someFunc(SomeClass obj) {
        obj.val = 10;
        obj = null;
    }

    // 1. for primitives types also java is pass by value;
    // 2. primitive types can't be null i.e they cannot be destroyed;
    static void otherFunc(int val) {
        val = 14;
        // val = null;
    }

    // 1. Java arrays are essentially class and behave exactly like some object
    // of a class
    static void arrFunc(int[] arr) {
        arr[0] = 99;
        arr = null;
        // arr[0] = null;
    }

    public static void main(String args[]) {
        SomeClass obj = new SomeClass(5);
        SomeClass verify;
        someFunc(obj);
        System.out.println("Object value: " + obj.val);
        // this output is from toString() it prints class name and hex hashcode;
        System.out.println("Object value: " + obj);

        // System.out.println("Object value: " + verify);

        // 1. Every class has a hashcode which is formed internally by Java
        // using memeory address of that object
        // 2. hashCode() is a one-way function java does not maintain a global internally
        // map of hash codes.
        // 3. Two objects can have exact same hash code.
        // 4. hash code does NOT transalte to exact memory
        // 5. hash code are primtive int types
        // 6. hash code can be negative
        System.out.println("Object hash: " + obj.hashCode());

        System.out.println(
            "is obj instance of SomeClass: " + (obj instanceof SomeClass)
        );

        System.out.println(
            "is obj.hashCode() int " +
                /*(obj.hashCode() instanceof Integer)*/ "true"
        );

        int[] arr;
        System.out.println("arr value: " + obj);
        arr = new int[1];
        arr[0] = 49;
        System.out.println("arr value: " + obj);
        arrFunc(arr);
        System.out.println("arr hash: " + arr.hashCode());
        System.out.println("arr[0] value: " + arr[0]);

        int val = 7;
        int chk;

        // 1. primitives type does not have a hash code as they are not objects.
        // System.out.println("Object hash: " + val.hashCode());
        // 2. unintialized primitives or objects can't be printed or work with
        otherFunc(val);
        System.out.println("val: " + val);
        // System.out.println("val: " + chk);
    }
}
