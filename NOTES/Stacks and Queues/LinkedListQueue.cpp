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

class LinkedListQueue
{
	private:
		struct Node * first;
		struct Node * last;

	public:
		LinkedListQueue()
		{
			first = NULL;
			last  = NULL;
		}

		LinkedListQueue(int val)
		{
			first = NULL;
			last  = NULL;
			enqueue(val);
		}

		void enqueue(int val)
		{
			struct Node * newlast = newNode(val);
			if(isEmpty())
			{
				first = newlast;
				last  = newlast;
			}
			else
			{
				last->next = newlast;
				last = newlast;
			}

		}

		void dequeue()
		{
			if(!isEmpty())
			{
				struct Node * temp = first;
				first = first->next;
				if(first==NULL)
					last = NULL;
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
	int c;
	string inp;
	LinkedListQueue q;
	while(true)
	{
		cin>>inp;
		if(inp=="-")
		{
			cout<<q.top()<<endl;
			q.dequeue();
		}
		else
		{
			c = stoi(inp);
			q.enqueue(c);
		}
		

	}
	return 0;
}