class WQUFPC {

    int[] arr;
    int comp;

    WQUFPC(int n) {
        arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = -1;
        }
        comp = n - 1;
    }

    /*
    2  3 5
    -3 2 3
    */
    int root(int idx) {
        while (arr[idx] > -1) {
            if (arr[arr[idx]] > -1) arr[idx] = arr[arr[idx]]; // PC
            idx = arr[idx];
        }
        return idx;
    }

    boolean find(int p, int q) {
        return root(p) == root(q);
    }

    /*
    2 3 5     6 7 9 10
    6 2 2    -7 6 6 6
    q          p
    */
    void union(int p, int q) {
        int proot = root(p);
        int qroot = root(q);
        if (proot == qroot) {
            return;
        }

        int szp = Math.abs(arr[proot]);
        int szq = Math.abs(arr[qroot]);

        if (szp > szq) {
            arr[proot] += arr[qroot];
            arr[qroot] = proot;
        } else {
            arr[qroot] += arr[proot];
            arr[proot] = qroot;
        }

        // System.out.println("p: "+p+" q: "+q);
        // printArr();

        comp--;
    }

    int components() {
        return comp;
    }

    void printArr() {
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
        System.out.println("--------------");
    }
}
