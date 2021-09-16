#include <iostream>
using namespace std;

struct Node
{
	int data;
	struct Node * left;
	struct Node * right;
	struct Node * parent;
};

Node* newNode(int data)
{
	struct Node * node = new struct Node();
	node->data         = data;
	node->left         = NULL;
	node->right        = NULL;
	node->parent       = NULL;
	return node;
}
/* 
InOrder Traversal ( Left, Root, Right )
Ex :-
							25
	   	   
	   	   15				  				   50
	
	10             22				35						70

4       12     18        24		 31		44				66		90

ans :-  L = left R = root H = right
		
L R  H  R  L  R  H   R  L  R  H  R  L  R  H
4 10 12 15 18 22 24  25 31 35 44 50 66 70 90 
< left > R < right  >   < left > R < right >
<		left        > R <       right      >

*/
//Complexity : Time O(n)
void printInOrder(struct Node * root)
{
	if(root==NULL)
		return;

	/* first recur on left child */
	printInOrder(root->left);

	/* then print the data of node */
	cout<<root->data<<" ";

	/* now recur on right child */
	printInOrder(root->right);

	/* after recursing both left and right return to parent */
	return;
}

/*
PreOrder Traversal ( Root, Left, Right ) : Depth-first traversal 
Ex :-
							25
	   	   
	   	   15				  				   50
	
	10             22				35						70

4       12     18        24		 31		44				66		90

ans :-  L = left R = root H = right

R  R  R  L H  R  L  H  R  R  L  H  R  L  H
25 15 10 4 12 22 18 24 50 35 31 44 70 66 90
R   R  < left >< right> R < left >< right >
R  <     left        > <      right       >

*/
// Complexity : Time O(n)
void printPreOrder(struct Node * root)
{
	if(root==NULL)
		return;

	/* first print data of node */
	cout<<root->data<<" ";

	/* then recur on left sutree */
	printPreOrder(root->left);

	/* now recur on right subtree */
	printPreOrder(root->right);

	/* after recursing both left and right return to parent */
	return;
}

/*
PostOrder Traversal ( Left, Right, Root ) : Depth-first traversal
Ex :-
							25
	   	   
	   	   15				  				   50
	
	10             22				35						70

4       12     18        24		 31		44				66		90

ans :-  L = left R = root H = right

L H  R  L  H  R  R  L  H  R  L  H  R  R  R
4 12 10 18 24 22 15 31 44 35 66 90 70 50 25
< left >< right > R < left >< right > R  R
<      left        ><     right        > R

*/
// Complexity : Time O(n)
void printPostOrder(struct Node * root)
{
	if(root==NULL)
		return;

	// first recur on left subtree
	printPostOrder(root->left);

	// then recur on right subtree
	printPostOrder(root->right);

	// now deal with the node
	cout<<root->data<<" ";

	/* after recursing both left and right return to parent */
	return;
}

/*
LevelOrder Traversal 
Ex :-
							25
	   	   
	   	   15				  				   50
	
	10             22				35						70

4       12     18        24		 31		44				66		90

ans :-

25 15 50 10 22 35 70 4 12 18 24 31 44 66 90
1  < 2 > <   3     > <         4          >   


//Function to print level order traversal of tree
printLevelOrder(tree)
for d = 1 to height(tree)
   printGivenLevel(tree, d);

//Function to print all nodes at a given level
printGivenLevel(tree, level)
if tree is NULL then return;
if level is 1, then
    print(tree->data);
else if level greater than 1, then
    printGivenLevel(tree->left, level-1);
    printGivenLevel(tree->right, level-1);
*/

//root -> depth = 0
//Complexity : Time O(n)
int depthOfTree(struct Node * root)
{
	if(root==NULL)
		return -1;
	else
	{
		int ldepth = depthOfTree(root->left);
		int rdepth = depthOfTree(root->right);

		if( ldepth > rdepth)
			return (ldepth+1);
		else
			return (rdepth+1);
	}
}

//Complexity : Time O(n)
void printGivenLevel(struct Node * root,int level)
{
	if      (root==NULL) return;
	if      (level == 0) cout<<root->data<<" ";
	else if (level >  0)
	{
		//level-1 takes to the desired level until
		//level-1 is not 1
		printGivenLevel(root->left,level-1);
		printGivenLevel(root->right,level-1);
	}
}

//Complexity : Time O(n^2)
void printLevelOrder(struct Node * root)
{
	int d = depthOfTree(root);
	int i;
	for(int i=0;i<=d;i++)
	{
		// i decides upto which level we have to
		// before starting to print
		printGivenLevel(root,i);
	}
}


/*
Spiral (->) Traversal
       (| )
       (<-)
       ( |)
       (->)
Ex :-
							25
	   	   
	   	   15				  				   50
	
	10             22				35						70

4       12     18        24		 31		44				66		90

ans :-

25 15 50 70 35 22 10 4 12 18 24 31 44 66 90
*/
//Complexity : Time O(n)
void printGivenSpiralLevel(struct Node * root,int level,int dir)
{
	if 		(root==NULL) return;
	else if (level == 0) cout<<root->data<<" ";
	else if (level  > 0)
	{
		if (dir%2!=0)
		{
			printGivenSpiralLevel(root->right,level-1,dir);
			printGivenSpiralLevel(root->left,level-1,dir);
		}
		else
		{
			printGivenSpiralLevel(root->left,level-1,dir);
			printGivenSpiralLevel(root->right,level-1,dir);
		}
	}
}
//Complexity : Time O(n^2)
void printSpiralOrder(struct Node * root)
{
	int d = depthOfTree(root);
	for(int i = 0;i<=d;i++)
		printGivenSpiralLevel(root,i,i);
}

/*
VerticalOrder Traversal
Ex :-
							25
	   	   
	   	   15				  				   50
	
	10             22				  35			 70

4       12     18        24		 31		  44	66		90

ans :- 

4 10 (15 12 18) 22 (25 24 31) 35 (50 44 66) 70 90
A B       C     D      E      F      G      H   I
*/
//Complexity : Time O(n)
void findMinMax(struct Node * root,int * min,int * max,int hd)
{
	//Base Case
	if (root == NULL) return;

	// Update min and max
	if      (hd < *min) *min = hd;
	else if (hd > *max) *max = hd;

	//Recur for left and right subtrees
	findMinMax(root->left,min,max,hd-1);
	findMinMax(root->right,min,max,hd+1);
}
//Complexity : Time O(n)
void printGivenVerticalLine(struct Node * root,int line,int hd)
{
	// Base Case
	if (root==NULL) return;

	// If this node is on given line number then
	if (hd == line) cout<<root->data<<" ";

	//Recur for left and right subtrees
	printGivenVerticalLine(root->left,line,hd-1);
	printGivenVerticalLine(root->right,line,hd+1);
}
//Complexity : Time O(n^2) [O(w*n) - w=width of BT]
void printVerticalOrder(struct Node * root)
{
	//Base Case
	if (root==NULL) return;

	int max = 0,min = 0;

	findMinMax(root,&min,&max,0);

	for(int line = min;line<=max;line++)
	{
		printGivenVerticalLine(root,line,0);
		cout<<endl;
	}
}

int main()
{
/*						 25
	   	   
	   	   8				  	       22
	
	6             3				 7			 20

5     11      2        1	 13	     0   15
*/
	
	struct Node * root = newNode(25);
	root->left = newNode(8);
	root->left->right = newNode(3);
	root->left->right->right = newNode(1);
	root->left->right->left = newNode(2);
	root->left->left = newNode(6);
	root->left->left->left  = newNode(5);
	root->left->left->right = newNode(11); 
	root->right = newNode(22);
	root->right->right = newNode(20);
	root->right->right->left = newNode(15);
	root->right->left = newNode(7);
	root->right->left->left = newNode(13);
	root->right->left->right = newNode(0);

	cout<<"InOrder       : "; printInOrder(root);
	cout<<endl;

	cout<<"PreOrder      : "; printPreOrder(root);
	cout<<endl;

	cout<<"PostOrder     : "; printPostOrder(root);
    cout<<endl;
	
	cout<<"LevelOrder    : "; printLevelOrder(root);
	cout<<endl;

	cout<<"SpiralOrder   : "; printSpiralOrder(root);
	cout<<endl;

	cout<<endl;
	cout<<"VerticalOrder : \n"; printVerticalOrder(root);
	cout<<endl;


	return 0;
}