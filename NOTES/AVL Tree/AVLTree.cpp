#include <iostream>
using namespace std;

/*
T1, T2 and T3 are subtrees of the tree rooted with y (on left side) 
or x (on right side)           

                y                               x
               / \     Right Rotation          /  \
              x   T3   – – – – – – – >        T1   y 
             / \       < - - - - - - -            / \
            T1  T2     Left Rotation            T2  T3

Keys in both of the above trees follow the following order 
      keys(T1) < key(x) < keys(T2) < key(y) < keys(T3)
So BST property is not violated anywhere.

T1, T2, T3 and T4 are subtrees. x is the new key inserted.

A) Left Left Case

         z                                      y 
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \ 
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2

B) Left Right Case

     z                               z                           x
    / \                            /   \                        /  \ 
   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
T1   x                          y    T3                    T1  T2 T3  T4
    / \                        / \
  T2   T3                    T1   T2

C) Right Right Case

  z                                y
 /  \                            /   \ 
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4

D) Right Left Case

   z                            z                            x
  / \                          / \                          /  \ 
T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
   x   T4                      T2   y                  T1  T2  T3  T4
  / \                              /  \
T2   T3                           T3   T4
*/

struct Node
{
	int data;
	int apparentHeight;
	struct Node * left;
	struct Node * right;
};

Node* newNode(int key)
{
	struct Node * node   = new struct Node;
	node->data 		     = key;
	node->apparentHeight = 0;
	node->left           = NULL;
	node->right          = NULL;
}

class AVLtree
{
	private:
		struct Node * root;

		int max(int i,int j)
		{
			return ((i > j) ? i : j);
		}

		int height(struct Node * x)
		{
			if (x==NULL) return -1;
			return x->apparentHeight;
		}


		int getBalance(struct Node * x)
		{
			if (x==NULL) return 0;
			return (height(x->left)-height(x->right));
		}

		Node* rightRotate(struct Node * y)
		{
			struct Node * x  = y->left;
			struct Node * T2 = x->right;

			// Perform Rotations
			x->right = y;
			y->left  = T2;

			//Update Heights
			y->apparentHeight = 1 + max(height(y->left),height(y->right));
			x->apparentHeight = 1 + max(height(x->left),height(x->right));

			//Return new root
			return x;
		}

		Node* leftRotate(struct Node * x)
		{
			struct Node * y  = x->right;
			struct Node * T2 = y->left;

			// Perform Rotation
			y->left  = x;
			x->right = T2;

			//Update heights
			x->apparentHeight = 1 + max(height(x->left),height(x->right));
			y->apparentHeight = 1 + max(height(y->left),height(y->right));

			//Return new root;
			return y;
		}

		/*
		The AVL trees are more balanced compared to Red Black Trees, 
		but they may cause more rotations during insertion and deletion.
		So for frequent insertions and deletions, use Red Black trees. 
		And if the insertions and deletions are less frequent and search 
		is more frequent operation, then use AVL tree.
		*/
		// Complexity : Time O(h) where h = lg n
		Node* insert(struct Node * root,int key)
		{
			if  	(root==NULL) return newNode(key);
			else if (key < root->data)
				root->left  = insert(root->left,key);
			else if (key > root->data)
				root->right = insert(root->right,key);
			else if (key == root->data)
				root->data = key;

			root->apparentHeight = 1+max(height(root->left),height(root->right));

			int balance = getBalance(root);

			// key is just a way to identify where the new key gets
			// inserted, can use getBalance also to find where the new key
			// gets inserted but is costly since getBalance takes some time.
			if (balance>1 && key < root->left->data)
					return rightRotate(root);

			if (balance>1 && key > root->left->data)
			{
				root->left = leftRotate(root->left);
				return rightRotate(root);
			}
			
			if (balance<-1 && key > root->right->data)
				return leftRotate(root);

			if (balance<-1 && key < root->right->data)
			{
				root->right = rightRotate(root->right);
				return leftRotate(root);
			}
			

			return root;
		}

		Node* deleteMin(struct Node * root)
		{
			if (root == NULL) return NULL;
			if (root->left == NULL) return root->right;
			root->left = deleteMin(root->left);
			root->apparentHeight = 1+max(height(root->left),height(root->right));

			int balance = getBalance(root);

			if (balance > 1 && getBalance(root->left)>=0)
				return rightRotate(root);

			if (balance > 1  && getBalance(root->left)<0)
			{
				root->left = leftRotate(root->left);
				return rightRotate(root);
			}

			if (balance < -1 && getBalance(root->right)<=0)
				return leftRotate(root);

			if (balance < -1 && getBalance(root->right)>0)
			{
				root->right = rightRotate(root->right);
				return leftRotate(root);
			}

			return root;
		}

		/*
		Let z be the first unbalanced node, y be the larger height 
		child of z, and x be the larger height child of y.
		The current node must be one of the ancestors of the deleted 
		node. Update the height of the current node.
		*/
		// Hibbard Deletion
		Node* deleteKey(struct Node * root,int key)
		{
			if 		(root==NULL) return NULL;
			else if (key < root->data)
				root->left  = deleteKey(root->left,key);
			else if (key > root->data)
				root->right = deleteKey(root->right,key);
			else
			{
				if (root->right==NULL) return root->left;

				struct Node * t = root;
				root = root->right;
				while(root->left != NULL)
					root = root->left;
				root->right = deleteMin(t->right);
				root->left  = t->left;
				delete t;

			}

			root->apparentHeight = 1+max(height(root->left),height(root->right));

			int balance = getBalance(root);

			if (balance > 1 && getBalance(root->left) >= 0)
				return rightRotate(root);

			if (balance > 1 && getBalance(root->left) < 0)
			{
				root->left = leftRotate(root->left);
				return rightRotate(root);
			}

			if (balance < -1 && getBalance(root->right)<= 0)
				return leftRotate(root);

			if (balance < -1 && getBalance(root->right) > 0)
			{
				root->right = rightRotate(root->right);
				return leftRotate(root);
			}
			
			return root;			


		}

		void printInorder(struct Node * root)
		{
			if (root==NULL) return;
			printInorder(root->left);
			cout<<root->data<<" ";
			printInorder(root->right);
			return;
		}

		void printLevelOrder(struct Node * root)
		{
			int d = height(root);
			for(int i = 0;i<=d;i++)
				printGivenLevel(root,i);
		}

		void printGivenLevel(struct Node * root,int level)
		{
			if      (root==NULL) return;
			else if (level==0) cout<<root->data<<" ";
			else
			{
				printGivenLevel(root->left,level-1);
				printGivenLevel(root->right,level-1);
			}
			return;
		}

	public:
		AVLtree()
		{
			root = NULL;
		}

		void insert(int key)
		{
			root = insert(root,key);
		}

		void deleteKey(int key)
		{
			root = deleteKey(root,key);
		}

		int height()
		{
			return height(root);
		}

		void printInorder()
		{
			printInorder(root);
			cout<<endl;
		}

		void printLevelOrder()
		{
			printLevelOrder(root);
			cout<<endl;
		}


};

int main()
{
	// 9
	// 9 5 10 0 6 11 -1 1 2
	AVLtree b;
	int n,input; cin>>n;
	while(n--)
	{
		cin>>input;
		b.insert(input);
	}
	b.printLevelOrder();
	b.printInorder();
	return 0;

}