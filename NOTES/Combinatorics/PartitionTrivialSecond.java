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

    0=1 1=2
    k=0              00000
    k=1     1000       0100   0010     0001
    k=2   110 101 -   011  -   -

    Now reverse 0=2 1=1

    1100 or 1000 & 0100 = 0100 or 0000
    1100 or 1000 ^ 0100 = 1000 or 1100

*/
public class PartitionTrivialSecond {

    private static int ans = 0;

    static boolean checkFor1(long bits, int k) {
        return (bits & (1L << k)) == 0L;
    }

    static long flipAtk(long bits, int k) {
        return (bits ^ (1L << k));
    }

    public static void recurse(long bits, int k, int len) {
        ans++;
        for (int i = k + 1; i < len; i++) {
            bits = flipAtk(bits, i - 1);
            recurse(bits, i, len - 1);
            bits = flipAtk(bits, i - 1);
        }
    }

    public static void main(String args[]) {
        int n = Integer.parseInt(args[0]);

        long bits = 0L;
        int len = 64;

        recurse(bits, 0, n);

        System.out.println(
            "No of ways to write " + args[0] + " in 1s and 2s are: " + (ans)
        );
        return;
    }
}
