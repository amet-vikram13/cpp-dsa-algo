#include <iostream>
#include <set>
#include <deque>
#include <cstdio>
using namespace std;

struct Node
{
	int sum;
	int depth;
	struct Node * deqA;
	struct Node * deqB;
};

void push(struct Node * temp,int dataA,int dataB,int x)
{
	if(temp==NULL)
		return;

	if(temp->sum > x)
		return;

	push(temp->deqA,dataA,dataB,x);
	

	if(dataA!=-1 && dataB!=-1)
	{
		struct Node * newnodeA = new struct Node;
		newnodeA->deqA = NULL; newnodeA->deqB = NULL;
		newnodeA->sum = temp->sum + dataA;
		newnodeA->depth = temp->depth + 1;
		temp->deqA = newnodeA;

		struct Node * newnodeB = new struct Node;
		newnodeB->deqA = NULL; newnodeB->deqB = NULL;
		newnodeB->sum = temp->sum + dataB;
		newnodeB->depth = temp->depth + 1;
		temp->deqB = newnodeB;
	}
	else
	{
		if(dataA==-1)
		{
			struct Node * newnodeB = new struct Node;
			newnodeB->deqA = NULL; newnodeB->deqB = NULL;
			newnodeB->sum = temp->sum + dataB;
			newnodeB->depth = temp->depth + 1;
			temp->deqB = newnodeB; 

			temp->deqA = NULL;
		}
		else
		{
			struct Node * newnodeA = new struct Node;
			newnodeA->deqA = NULL; newnodeA->deqB = NULL;
			newnodeA->sum = temp->sum + dataA;
			newnodeA->depth = temp->depth + 1;
			temp->deqA = newnodeA;	

			temp->deqB = NULL;
		}
	}

	push(temp->deqB,dataA,dataB,x);
}

void push_in(struct Node ** headref,int dataA,int dataB,int x)
{
	struct Node * temp = (*headref);
	push(temp->deqA,dataA,dataB,x);
	push(temp->deqB,dataA,dataB,x);
}

void findMax(struct Node * temp,set<int>& moves,int x)
{
	if(temp==NULL)
		return;
	
	if(temp->sum > x)
		return;

	findMax(temp->deqA,moves,x);

	moves.insert(temp->depth);

	findMax(temp->deqB,moves,x);
}



void search(struct Node ** (headref),set<int>& moves,int x)
{
	struct Node * temp = (*headref);
	moves.insert(temp->depth);
	findMax(temp->deqA,moves,x);
	findMax(temp->deqB,moves,x);
}



void Print(struct Node *root)
{
    
   if ( NULL == root )
      return;
	
   
     Print(root->deqA);

   
   
     printf("%d ", root->sum );

  
   
    Print(root->deqB);
}


int main()
{
	int g,n,m,x,input;
    cin>>g;
    
    while(g--)
    {    
        
        set<int> moves;
        deque<int> A; deque<int> B;
        cin>>n>>m>>x;

        for(int i=0;i<n;i++)
        {
            cin>>input;
            A.push_back(input);
        }
        
        for(int i=0;i<m;i++)
        {
            cin>>input;
            B.push_back(input);
        }

        struct Node * head = new struct Node;
        struct Node * nodeA = new struct Node;
        struct Node * nodeB = new struct Node;

		head->deqA = nodeA; 
		head->deqB = nodeB;
		head->depth = 0;
        
        nodeA->sum = A.front(); A.pop_front();
        nodeA->deqA = NULL; 
        nodeA->deqB = NULL;
        nodeA->depth = 1;
        
        nodeB->sum = B.front(); B.pop_front();
        nodeB->deqA = NULL; 
        nodeB->deqB = NULL;
        nodeB->depth = 1;

        int a,b;

        while(!A.empty() && !B.empty())
        {
        	a = A.front(); b = B.front();
        	push_in(&head,a,b,x);
        	A.pop_front(); B.pop_front();
        }

        while(!A.empty())
        {
        	a = A.front();
        	push_in(&head,a,-1,x);
        	A.pop_front();
        }

        while(!B.empty())
        {
        	b = B.front();
        	push_in(&head,-1,b,x);
        	B.pop_front();
        }

        Print(head);
        cout<<endl;


        //search(&head,moves,x);

        //cout<<*(moves.rbegin())<<endl;
    }

    return 0;
}