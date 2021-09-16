#include <iostream>
using namespace std;

struct Node
{
	int data;
	struct Node * next;
}

void detectAndRemoveLoop(struct Node * head)
{
	if(head==NULL || head->next==NULL)
		return;

	struct Node * slow_p = head;
	struct Node * fast_p = head;

	while(slow_p!=NULL && fast_p!=NULL && fast_p->next!=NULL)
	{
		slow_p = slow_p->next;
		fast_p = fast_p->next->next;

		if(slow_p==fast_p)
			break;
		
	}

	if(slow_p==fast_p)
	{
		struct Node * ptr1;
		struct Node * ptr2;

		ptr1 = head;
		while(1)
		{
			ptr2 = slow_p;
			while(ptr2->next!=slow_p && ptr2->next!=head)
				ptr2 = ptr2->next;

			if(ptr2->next == ptr1)
				break;

			ptr1 = ptr1->next;
		}

		ptr2->next = NULL;
	}

	return false;
}
