class TrieNode {

    public TrieNode[] next;
    public int level;
    public boolean isWord;

    public TrieNode(int h) {
        next = new TrieNode[27];
        isWord = false;
        level = h;
    }
}

class Trie {

    private TrieNode root;
    private boolean isPrefix;

    private int charIdx(String word, int d) {
        if (word.charAt(d) == '.') return -1;
        return word.charAt(d) - 'a';
    }

    private TrieNode _insert(TrieNode itr, String word, int d) {
        if (itr == null) itr = new TrieNode(d);
        if (word.length() == d) {
            itr.isWord = true;
            return itr;
        }
        int c = charIdx(word, d);
        itr.next[c] = _insert(itr.next[c], word, d + 1);
        return itr;
    }

    private boolean _get(TrieNode itr, String word, int d) {
        if (itr == null) return false;
        if (word.length() == d) {
            return (isPrefix ? true : (itr.isWord ? true : false));
        }
        int c = charIdx(word, d);
        return _get(itr.next[c], word, d + 1);
    }

    // private boolean _get(TrieNode itr, String word, int d) {
    //     if (itr == null) return false;
    //     if (word.length() == d) {
    //         return itr.isWord;
    //     }
    //     int idx = idxAtChar(word, d);
    //     boolean match = false;
    //     if (idx == -1) {
    //         for (int i = 0; i < 26; i++) {
    //             match = _get(itr.next[i], word, d + 1);
    //             if (match) break;
    //         }
    //         return match;
    //     }
    //     return _get(itr.next[idx], word, d + 1);
    // }

    public Trie() {
        root = new TrieNode();
    }

    public void insert(String word) {
        root = _insert(root, word, 0);
    }

    public boolean search(String word) {
        isPrefix = false;
        return _get(root, word, 0);
    }

    public boolean startsWith(String prefix) {
        isPrefix = true;
        return _get(root, prefix, 0);
    }
}
