// Longest Common Prefix

#include <iostream>
#include <string>
using namespace std;

struct Node
{
	Node* next[26];
	int count;
	Node()
	{
		count = 0;
		for(int i=0;i<26;i++)
			next[i] = NULL;
	}
};

class Trie
{
	private:
		Node* root;
		int max_words;

		int charAtd(string key,int d)
		{
			if (d < key.size()) return key[d]-'a';
			return -1;
		}

		char getChar(int i)
		{ return char(int('a')+i); }

		Node* _push(Node* x,int d,string key)
		{
			if (x == NULL) x = new Node();
			if (d == key.size()) return x;
			int c = charAtd(key,d);
			x->next[c] = _push(x->next[c],d+1,key);
			x->next[c]->count += 1;
			return x;
		}

		string _getLCP(Node* x)
		{
			int c; int flag = 0;
			for(int i=0;i<26 && flag<2;i++)
			{
				if (x->next[i]!=NULL)
				{
					flag += 1;
					c = i;
				}
			}
			string ans = "";
			if (flag==0 || flag>1)
			{
				if (x == root)
				{
					ans.push_back('-');
					ans.push_back('1');
				}
				return ans;
			}

			if (x->next[c]->count != max_words)
				return ans;
			ans.push_back(getChar(c));
			ans = ans + _getLCP(x->next[c]);
			return ans;
		}

	public:
		Trie(int n_inp)
		{
			root = new Node();
			max_words = n_inp;
		}

		void push(string key)
		{	root = _push(root,0,key); }

		string getLCP()
		{	return _getLCP(root); }
};

string _commonPrefix(string s1,string s2)
{
	string prefix = "";
	for(int i=0,j=0;i<s1.size()&&j<s2.size();i++,j++)
	{
		if(s1[i]==s2[j])
			prefix.push_back(s1[i]);
		else
			break;
	}
	return prefix;
}

string commonPrefix(string* arr,int n)
{
	string prefix = arr[0];
	for(int i=1;i<n && !prefix.empty();i++)
		prefix = _commonPrefix(prefix,arr[i]);

	if (prefix.empty())
		return "-1";

	return prefix;
}

int main()
{
	int t,n; cin >> t;
	string* arr;
	while(t--)
	{
		cin >> n;
		arr = new string[n];
		for(int i=0;i<n;i++)
			cin >> arr[i];
		cout << commonPrefix(arr,n) << endl;
		delete [] arr;
	}
	return 0;
}

/* Trie Solution
int main()
{
	int t,n; cin >> t;
	string inp;
	Trie* tr;
	while(t--)
	{
		cin >> n;
		tr = new Trie(n);
		while(n--)
		{
			cin >> inp;
			tr->push(inp);
		}
		cout << tr->getLCP() << endl;
	}
	return 0;
}
*/
