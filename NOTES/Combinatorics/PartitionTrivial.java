/*
                5
        2               3
    1       1       1       2
                        1       1

                        5
                4               1
            3       1
        1       2


    Possible solutions :-
    {1,1,1,1,1}
    {1,1,1,2}
    {2,1,1,1}


    3 = {{1,1,1},{1,2},{2,1}}
    4 = {{1,1,1,1},{2,2},{1,1,2},{1,2,1},{2,1,1}}
    4 = {{1,1,1,1},
    {2,1,1} , {{1,2,1}} , {{1,1,2}}
    {2,2}}

    4 = {{1,1,1,1},
    {2,-1,1,1} , {{1,2,-1,1}} {{1,1,2,-1}}
    {2,-1,2,-1}}              {{2,-1,2,-1}}

    5 = {{1,1,1,1,1},
    {{2,1,1,1,}}  {1,2,1,1}     {1,1,2,1}  {1,1,1,2}
    {2,2,1}       {1,2,2}      {2,1,2}

    00000
    1000  0100 0010 0001
    110   011  101

    k=0;
*/

public class PartitionTrivial {

    private static int ans = 0;

    public static void printArr(byte[] arr) {
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] != -1) {
                System.out.print(arr[i] + " ");
            }
        }
        System.out.println();
        System.out.println("------------");
    }

    public static void recurse(byte[] arr, int k) {
        ans++;
        for (int i = k; i + 1 < arr.length; i++) {
            if (arr[i] == 1 && arr[i + 1] == 1) {
                arr[i] = 2;
                arr[i + 1] = -1;
                printArr(arr);
                recurse(arr, i + 1);
                arr[i] = 1;
                arr[i + 1] = 1;
            }
        }
    }

    public static void main(String args[]) {
        int n = Integer.parseInt(args[0]);

        byte[] arr = new byte[n];

        for (int i = 0; i < n; i++) {
            arr[i] = 1;
        }

        recurse(arr, 0);

        System.out.println(
            "No of ways to write " + args[0] + " in 1s and 2s are: " + (ans - 1)
        );
        return;
    }
}
