#include <iostream>
#include <cstdlib>
using namespace std;

struct Node{
	int data;
	struct Node * next;
};

void push(struct Node ** headref,int n)
{
	// Allocate a new node and its pointer
	struct Node * new_node = new struct Node;

	// Put in data
	new_node->data = n;

	// Make next of new_node as head
	new_node->next = (*headref);

	// change head reference, note *head = pointer NOT address bcoz *& cancels each other
	*headref = (new_node);
}

void deletenode(struct Node ** headref,int key)
{
	struct Node * prev;
	struct Node * temp = *headref;

	if(temp!=NULL && temp->data==key)
	{
		*headref = temp->next;
		free(temp);
		return;
	}

	while(temp!=NULL && temp->data!=key)
	{
		prev = temp;
		temp = temp->next;
	}

	if(temp==NULL) return;

	prev->next = temp->next;
	free(temp);
}

void printll(struct Node * n)
{
	while(n!=NULL)
	{
		cout<<n->data<<" ";
		n=n->next;
	}
	cout<<endl;
}

int main()
{
    /* Start with the empty list */
    struct Node* head = NULL;
 
    push(&head, 7);
    push(&head, 1);
    push(&head, 3);
    push(&head, 2);
 
   
    printll(head);
    deletenode(&head, 1);
    printll(head);
    return 0;
}