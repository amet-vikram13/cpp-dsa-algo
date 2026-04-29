class TrieNode {

    boolean isWord;
    TrieNode[] next;

    TrieNode() {
        isWord = false;
        next = new TrieNode[26];
    }
}

public class Trie {

    TrieNode root;

    int idxForCharAt(String word, int d) {
        return word.charAt(d) - 'a';
    }

    TrieNode put(TrieNode itr, String word, int d) {
        if (itr == null) itr = new TrieNode();
        if (d == word.length()) {
            itr.isWord = true;
            return itr;
        }
        int c = idxForCharAt(word, d);
        itr.next[c] = put(itr.next[c], word, d + 1);
        return itr;
    }

    Trie() {
        root = null;
    }
}
