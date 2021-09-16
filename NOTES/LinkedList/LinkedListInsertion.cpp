#include <iostream>
using namespace std;

struct Node{
	int data;
	struct Node * next;
};

void printll(struct Node *);
void push(struct Node **,int);
void insertafter(struct Node *,int);
void append(struct Node **,int);


int main()
{
		
	struct Node * head = new struct Node;
	struct Node * second = new struct Node;
	struct Node * third = new struct Node;

	head->next = second;
	second->next = third;
	third->next = NULL;

	head->data = 1;
	second->data = 2;
	third->data = 4;

	printll(head);
	push(&head,0);
	printll(head);
	insertafter(second,3);
	printll(head);
	append(&head,5);
	printll(head);
	
	/*
	struct Node * head = NULL;

	insertafter(head,0);
	append(&head,1);
	insertafter(head,2);
	push(&head,0);
	append(&head,3);
	printll(head);
	*/
	
	return 0;
}

void printll(struct Node * n)
{
	struct Node * temp = n;
	while(temp!=NULL)
	{
		cout<<temp->data<<" ";
		temp=temp->next;
	}
	delete temp;
	cout<<endl;
}

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

void insertafter(struct Node * prev_node,int n)
{
	/*	
	if(prev_node->next == NULL)
	{
		cout<<"The given previous node cant be Last node.\n";
		return;
	}
	OR */
	
	if(prev_node == NULL)
	{
		cout<<"The Linked List must have atleast one node.\n";
		return;
	}	
	
	// Allocate new node and its pointer and put in data
	struct Node * new_node = new struct Node;
	new_node->data = n;

	// Insert it in after previous node
	new_node->next = prev_node->next;
	prev_node->next = new_node;

}

void append(struct Node ** headref,int n)
{
	// Allocate new node and its pointer and put in data
	struct Node * new_node = new struct Node;
	new_node->data = n;

	// Since Last Node so next is NULL
	new_node->next = NULL;

	// Iterative variable 
	struct Node * last = *headref;

	// If head is NULL
	if(*headref==NULL)
	{
		*headref = new_node;
		return;
	}

	while(last->next != NULL)
		last = last->next;

	last->next = new_node;
	
}
