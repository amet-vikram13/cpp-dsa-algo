#include <iostream>
#include <string>
using namespace std;

/*
A Trie Node 
-> Can store upto 26 different pointers to Tire Node
   and an integer value
*/
struct Node
{
	int value;
	Node* next[26];
	Node()
	{
		value = -1;
		for(int i=0;i<26;i++)
			next[i] = NULL;
	}
};

/* A Trie Class 
-> A Trie object will store any word
   as key and a value, val at the LAST
   character of the word only, rest of the
   characters store -1 as default

   Eg:- sea,3  seat,5  sell,6  set,1 
   
   Trie :
	
	root -> s -> e -> a(3) -> t(5)
	             |
				 t(1)

	Only words with characters (a-z) allowed. 
*/
class Trie
{
	private:
		Node* root;

		// Utility func 
		int charAtd(string key,int d)
		{
			if (d < key.size()) return key[d]-'a';
			return -1;
		}

		/* 
		Utility func for put(string inp,int val)
		-> Implemented as Recursion
		-> Logic similar to insert func in BT and BST
		*/
		Node* _put(Node* x,string key,int val,int d)
		{
			if (x == NULL) { x = new Node(); }
			if (d == key.size())
			{
				x->value = val;
				return x;
			}
			int c = charAtd(key,d);
			x->next[c] = _put(x->next[c],key,val,d+1);
			return x;
		}

		/* 
		Utility func for get(string inp)
		-> Implemented as Recursion
		-> Logic similar to get func in BT and BST
		*/
		int _get(Node* x,string key,int d)
		{
			if (x == NULL) return -1;
			if (d == key.size()) return x->value;
			int c = charAtd(key,d);
			return _get(x->next[c],key,d+1);
		}

		/*
		Function to CHECK if given node can be deleted
		*/
		bool deleteGivenNode(Node** z)
		{
			Node* x = (*z);
			bool flag = false;
			if (x != NULL)
			{ 
				// If this node stores value for some other
				// word then this node cannot be deleted.
				if (x->value == -1)
				{
					bool tmp = true;
					// If any one of the children nodes
					// is not NULL, the given node
					// can not be deleted
					for(int i=0;i<26 && tmp;i++)
						if (x->next[i]!=NULL)
							tmp = false;
											
					// If all children nodes are NULL
					// then no need for the given node
					// to exist, efficient for memory to delete
					// the node.
					if (tmp)
					{
						// function returns a boolean value if any 
						// node is deleted as this will be used to 
						// check whether the parent of the given 
						// node can be deleted
						flag = true;
						Node* node = x;
						x = NULL;
						delete node;
					}
				}
			}
			(*z) = x;
			return flag;
		}

		/*
		Utility func for deleteNode(string inp)
		- Implemented as Recursion
		- Logic similar to delete in BT and BST with an
		  additional utility function deleteGivenNode(Node** x)
		*/
		Node* _deleteNode(Node* x,string key,int d,bool* flag)
		{
			if (x == NULL) return x;
			if (d == key.size()-1)
			{
				int c = charAtd(key,d);
				// Once we found the NEXT NODE
				// POINTING to LAST character of the
				// word we makes it value -1 as this word
				// is no longer part of Trie obj
				if (x->next[c] != NULL)
				{
					if (x->next[c]->value != -1)
					{
						x->next[c]->value = -1;
						// x->next[c] node is now checked whether it can be deleted
						(*flag) = deleteGivenNode(&(x->next[c]));	
					}
				}
				return x;
			}
			int c = charAtd(key,d);
			x->next[c] = _deleteNode(x->next[c],key,d+1,flag);
			// Now If (*flag) is true then
			// that means, child of x->next[c] is deleted
			// so now x->next[c] node is now checked whether it
			// can be deleted altogether if there are no other children
			if ((*flag))
				(*flag) = deleteGivenNode(&(x->next[c]));
			return x;
		}

	public:
		Trie()
		{
			root = new Node();
		}

		void put(string key,int val)
		{ 
			root = _put(root,key,val,0);
			cout << "key inserted: " << key << endl;
		 }

		int get(string key)
		{ 
			return _get(root,key,0); 
		}

		void deleteNode(string key)
		{ 
			bool* flag = new bool;
			(*flag) = false;
			root = _deleteNode(root,key,0,flag);
			if ((*flag))
				(*flag) = deleteGivenNode(&(root->next[charAtd(key,0)]));
			delete flag;
			cout << "key deleted: " << key << endl; 
		}
};

int main()
{
	Trie tr;
	cout << "Usage:\n";
	cout << "    Put: 1 key value\n";
	cout << "    Get: 2 key\n";
	cout << "    Delete: 3 key\n";
	cout << "    Terminate: -1\n";

	int ops,value;
	string key;
	bool flag = true;
	while(flag)
	{
		cin >> ops;
		switch(ops)
		{
			case 1:
				cin >> key >> value;
				tr.put(key,value);
				break;
			case 2:
				cin >> key;
				cout << tr.get(key) << endl;
				break;
			case 3:
				cin >> key;
				tr.deleteNode(key);
				break;
			case -1:
				flag = false;
				break;
			default:
				cout << "Not a valid command\n";
				flag = false;
		}
	}

	return 0;
}