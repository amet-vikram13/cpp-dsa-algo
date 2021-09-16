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

		int sizePQ()
		{
			return size;
		}

		int topMin()
		{
			return pq[1];
		}

		void delMin()
		{
			exch(1,N--);
			pq[N+1] = -1;
			size--;
			sink(1);
		}

		bool isEmpty()
		{
			return size==0;
		}

};

int main()
{
	MinPQ pq(11);
	int input;
	while(true)
	{
		cin>>input;

		if(input==-1)
			pq.delMin();
		else
		{
			pq.insert(input);
			cout<<pq.topMin()<<endl;
		}
	}
}