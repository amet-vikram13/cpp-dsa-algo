#include <bits/stdc++.h>
using namespace std;

/*
To decode the encoded data we require the Huffman tree. We iterate through the binary encoded data. To find 
character corresponding to current bits, we use following simple steps.

1. We start from root and do following until a leaf is found.
2. If current bit is 0, we move to left node of the tree.
3. If the bit is 1, we move to right node of the tree.
4. If during traversal, we encounter a leaf node, we print character of that particular leaf node and then 
   again continue the iteration of the encoded data starting from step 1.
*/

// A Huffman Tree node
struct Node
{
	char var;
	int freq;
	struct Node * left;
	struct Node * right;
};

Node* newNode(char data,int occur)
{
	struct Node * node = new struct Node;
	node->var = data;
	node->freq = occur;
	node->left = NULL;
	node->right = NULL;
	return node;
}


class HuffmanCoding	
{
	private:
		string str;
		char * arr;
		int  * freq;
		int n;
		queue<Node*> q1;
		queue<Node*> q2;
		struct Node * root;

		// Utility funtion to extract Node with min freq from q1 and q2
		Node* extractMin()
		{
			struct Node * min;
			if(!q1.empty() && !q2.empty())
			{
				if(q1.front()->freq < q2.front()->freq)
				{
					min = q1.front();
					q1.pop();
				}
				else
				{
					min = q2.front();
					q2.pop();
				}
				return min;
			}
			else if (!q1.empty())
			{
				min = q1.front();
				q1.pop();
				return min;
			}
			else if (!q2.empty())
			{
				min = q2.front();
				q2.pop();
				return min;
			}
			return NULL;
		}

		// building huffman Tree
		Node* buildHuffmanTree()
		{
			for(int i=0;i < n;i++)
				q1.push(newNode(arr[i],freq[i]));


			while(q1.size()+q2.size()!=1)
			{
				struct Node * x = extractMin();
				struct Node * y = extractMin();
				struct Node * n = newNode('#',x->freq+y->freq);
				n->left = x;
				n->right = y;
				q2.push(n);
			}
			root = q2.front();
			q2.pop();
		}

		void printCodes(struct Node * curr, int code[], int top)
		{
			// Assign 0 to left edge and recur
		    if (curr->left) 
		    {
		 
		        code[top] = 0;
		        printCodes(curr->left, code, top + 1);
		    }
		 
		    // Assign 1 to right edge and recur
		    if (curr->right) 
		    {
		 
		        code[top] = 1;
		        printCodes(curr->right, code, top + 1);
		    }
		 
		    // If this is a leaf node, then
		    // it contains one of the input
		    // characters, print the character
		    // and its code from code[]
		    if (!curr->right && !curr->left) 
		    {
		        cout<<curr->var<<" : ";
		        int i;
		    	for (i = 0; i < top; ++i)
		    		cout<<code[i];
		    	cout<<endl;
		    }
		}

		int depth(struct Node * curr)
		{
			if (curr == NULL)
				return -1;
			else
			{
				int ldepth = depth(curr->left);
				int rdepth = depth(curr->right);
				return ((ldepth > rdepth) ? 1+ldepth : 1+rdepth);
			}
		}

		void printLevelOrder(struct Node * curr,int level)
		{
			if (curr == NULL)
				return;
			if (level == 0)
				cout<<curr->var<<":"<<curr->freq<<"  ";
			else
			{
				printLevelOrder(curr->left,level-1);
				printLevelOrder(curr->right,level-1);
			}
		}

		int randomPartition(int p,int r)
		{
			int random = (p + rand()%(r-p+1));
			int pivot  = freq[random];
			
			int  temp1 = freq[random]; 
			char temp2 = arr[random];
			freq[random] = freq[r];
			arr[random]  = arr[r];
			freq[r] = temp1;
			arr[r]  = temp2;
		
			int i = p-1,j;

			for(int j=p;j < r;j++)
			{
				if(freq[j] < pivot)
				{
					i++;
					temp1   = freq[j];
					freq[j] = freq[i];
					freq[i] = temp1;

					temp2   = arr[j];
					arr[j] = arr[i];
					arr[i] = temp2;
				}
			}
			temp1   = freq[r];
			freq[r] = freq[i+1];
			freq[i+1] = temp1;

			temp2   = arr[r];
			arr[r] = arr[i+1];
			arr[i+1] = temp2;

			return (i+1);
		}

		void randomQuickSort(int l,int r)
		{
			if (l < r)
			{
				int p = randomPartition(l,r);
				randomQuickSort(l,p-1);
				randomQuickSort(p+1,r);
			}
		}

	public:
		HuffmanCoding(string input)
		{
			str = input;

			map<char,int> m;

			int i;
			for(i=0;i < str.size();i++)
				m[str[i]]++;

			n = m.size();

			arr  = new char[n];
			freq = new  int[n];

			i=0;
			for(auto it = m.begin();it!=m.end();it++)
			{
				arr[i]  = it->first;
				freq[i] = it->second;
				i++;
			}
			randomQuickSort(0,n-1);
			buildHuffmanTree();
		}

		void printHuffmanCodes()
		{
			struct Node * curr = root;
			int code[50];
			printCodes(curr,code,0);
		}

		void printHuffmanTree()
		{
			struct Node * curr = root;
			int d = depth(curr);
			for(int i=0;i <= d;i++)
			{
				curr = root;
				printLevelOrder(curr,i);
				cout<<endl;
			}
		}

		string decode(string s)
		{
			string ans = "";
			struct Node * curr = root;
			for(int i=0;i < s.size();i++)
			{
				if(s[i]=='0')
					curr = curr->left;
				else
					curr = curr->right;

				if(!curr->left && !curr->right)
				{
					ans += curr->var;
					curr = root;
				}
			}
			return ans;
		}
};

int main()
{
	HuffmanCoding hf("geeksforgeeks");
	hf.printHuffmanCodes();
	//hf.printHuffmanTree();
	cout<<hf.decode("10011111010001100100111100111110100")<<endl;

	return 0;
}