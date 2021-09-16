#include <iostream>
using namespace std;

class MinPQ
{
	private :
		
		int * pq;
		int N;
		int size;

		bool less(int i,int j)
		{	return pq[i]<pq[j]; }

		void exch(int i,int j)
		{
			int temp = pq[i];
			pq[i] = pq[j];
			pq[j] = temp;
		}

		void swim(int k)
		{
			while(k>1 && less(k,k/2))
			{
				exch(k,k/2);
				k = k/2;
			}
		}

		void sink(int k)
		{
			while(2*k<=N)
			{
				int j=2*k;

				if(j<N && less(j+1,j))
					j++;

				if(less(k,j))
					break;

				exch(k,j);

				k = j;
			}
		}

		void heapify()
		{
			for(int i = N/2;i>0;i--)
				sink(i);
		}

	public :

		MinPQ(int capacity)
		{
			pq = new int[capacity+1];
			N = 0;
			size = 0;
		}

		void insert(int key)
		{
			pq[++N] = key;
			size++;
			swim(N);
		}

		void delMin()
		{
			exch(1,N--);
			size--;
			sink(1);
		}

		void deleteEle(int v)
		{
			int i;
			for(i=1;i<=N;i++)
				if(pq[i]==v)
					break;

			if(i!=N)
			{
				pq[i] = pq[N--];
				heapify();
				return;
			}

			N--;

			return;
		}

		int topMin()
		{
			return pq[1];
		}

		int sizePQ()
		{
			return size;
		}

		bool isEmpty()
		{
			return size==0;
		}

		void printPQ()
		{
			for(int i=1;i<=N;i++)
				cout<<pq[i]<<" ";
			cout<<endl;
		}

};

int main()
{
	int Q,q,x; cin>>Q;
	MinPQ p(100000);
	while(Q--)
	{
		cin>>q;

		if     (q==1)
		{
			cin>>x;
			p.insert(x);
			//p.printPQ();
		}

		else if(q==2)
		{
			cin>>x;
			p.deleteEle(x);
			//p.printPQ();
		}

		else if(q==3)
		{
			cout<<p.topMin()<<endl;
			//p.printPQ();
		}
	}

	return 0;
}