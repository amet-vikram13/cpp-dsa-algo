#include <iostream>
#include <climits>
#include <string>
using namespace std;

struct Node
{
	int data;
	struct Node * next;
};

Node* newNode(int n)
{
	struct Node * node = new struct Node;
	node->data = n;
	node->next = NULL;
	return node;
}

class LinkedListStack
{
	private:
		struct Node * first;

	public:
		LinkedListStack()
		{
			first = NULL;
		}

		LinkedListStack(int val)
		{
			first = NULL;
			push(val);
		}

		void push(int val)
		{
			struct Node * newfirst = newNode(val);
			newfirst->next = first;
			first = newfirst;	
		}

		void pop()
		{
			if(!isEmpty())
			{
				struct Node * temp = first;
				first = first->next;
				delete temp;
			}	
		}

		int top()
		{
			if(!isEmpty())
				return first->data;
			else
				return INT_MIN;
		}

		bool isEmpty()
		{	return first==NULL; }

};

int main()
{
	string inp;
	int c;
	LinkedListStack s;
	while(true)
	{
		cin>>inp;
		if(inp=="-")
		{
			cout<<s.top()<<endl;
			s.pop();
		}
		else
		{
			c = stoi(inp);
			s.push(c);
		}
		

	}
	return 0;
}