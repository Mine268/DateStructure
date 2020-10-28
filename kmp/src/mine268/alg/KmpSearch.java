package mine268.alg;

import java.util.Scanner;

public class KmpSearch {

    /**
     * @author Mine268
     * searching for the substring with kmp-algo
     */
    public static int index(String s, String p) {
        int lp = p.length(), ls = s.length();
        char[] parr = p.toCharArray(), sarr = s.toCharArray();
        if (lp == 0)
            return -1;
        if (lp > ls)
            return -1;


        int[] next = new int[lp];
        next[0] = -1;
        if (lp > 1)
            next[1] = 0;

        for (int i = 2; i < lp; i++) {
            if (parr[i - 1] == parr[next[i - 1]])
                next[i] = next[i - 1] + 1;
            else {
                int q = next[i - 1];
                while (q != -1 && parr[q] != parr[i - 1])
                    q = next[q];
                next[i] = q + 1;
            }
        }

        int i = 0, j = 0;
        while (i < sarr.length && j < parr.length) {
            if (j == -1 || sarr[i] == parr[j]) {
                i++;
                j++;
            } else
                j = next[j];
        }
        if (j >= parr.length)
            return i - parr.length;
        else
            return -1;
    }

    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        String str, pat;
        str = reader.nextLine();
        pat = reader.nextLine();

        System.out.println(KmpSearch.index(str, pat));
    }
}
