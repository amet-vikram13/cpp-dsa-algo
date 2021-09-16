#include <iostream>
#include <set>
using namespace std;

struct Node
{
	// A T G C
	int pat_idx;
	Node* next[4];
	Node()
	{
		pat_idx = -1;
		for(int i=0;i<4;i++)
			next[i] = NULL;
	}
};

class Trie
{
	private:
		Node* root;
		set<int> idx;
		string txt;

		int charAtd(string key,int d)
		{
			if      (key[d]=='A') return 0;
			else if (key[d]=='T') return 1;
			else if (key[d]=='G') return 2;
			return 3;
		}

		Node* _push(Node* x,int d,string pat,int value)
		{
			if (x == NULL) x = new Node();
			if (d == pat.size()) 
			{
				x->pat_idx = value;
				return x;
			}
			int c = charAtd(pat,d);
			x->next[c] = _push(x->next[c],d+1,pat,value);
			return x;
		}

		bool _findPattern(Node* x,int d)
		{
			if (x == NULL) return false;
			if (d == txt.size()) return x->pat_idx!=-1;
			int c = charAtd(txt,d);
			//cout << "position at: " << d << " character: " << c << endl;
			bool ans = _findPattern(x->next[c],d+1);
			//cout << "pat_idx: " << x->pat_idx << endl;
			return (ans || (x->pat_idx!=-1));
		}

	public:
		Trie(string main_txt)
		{
			txt = main_txt;
			root = new Node();
		}

		void push(string pat,int value)
		{
			root = _push(root,0,pat,value);
		}

		void findPattern()
		{
			for(int i=0;i<txt.size();i++)
			{
				//cout << "starting at: " << i << endl;
				if(_findPattern(root,i))
					idx.insert(i);
			}
		}

		void printIdx()
		{
			set<int>::iterator itr;
			for(itr=idx.begin();itr!=idx.end();itr++)
				cout << *itr << " ";
			cout << endl;
		}
};

int main()
{
	ios_base::sync_with_stdio(false);
	string inp; cin >> inp;
	Trie tr(inp);
	int n; cin >> n;
	for(int i=0;i<n;i++)
	{
		cin >> inp;
		tr.push(inp,i);
	}
	tr.findPattern();
	tr.printIdx();
	return 0;
}