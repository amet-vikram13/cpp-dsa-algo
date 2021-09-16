#include <iostream>
using namespace std;

struct Node
{
	int data;
	struct Node * next;
};

void printlist(struct Node *);

int main()
{
	/* Instead what used below we could have also use
	following steps :-
	struct Node * head = NULL; // Create a NULL pointer-to-struct Node
	head = new struct Node;    // and then dynamically allocate memory
							   // to point to a struct Node
	
	but instead doing in two steps we can also allocate
	memory at the time of creating pointer only. */
	
	struct Node * head = new struct Node;
	struct Node * second = new struct Node;
	struct Node * third = new struct Node;

	head->data = 1;
	head->next = second;
	second->data = 2;
	second->next = third;
	third->data = 3;
	third->next = NULL;

	printlist(head);
	return 0;
}

void printlist(struct Node *n)
{
	struct Node * temp = n;	
	while(temp!=NULL)
	{
		cout<<temp->data<<" ";
		temp = temp->next;
	}
	delete temp;
	cout<<endl;
}

