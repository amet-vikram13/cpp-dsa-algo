#include <iostream>
using namespace std;

class MaxPQ
{
	private :
		char * pq;
		int N;
		int size;

		bool less(int i,int j)
		{
			return int(pq[i])<int(pq[j]);
		}

		void exch(int i,int j)
		{
			char temp = pq[i];
			pq[i] = pq[j];
			pq[j] = temp;
		}

		void swim(int k)
		{
			while(k>1 && less(k/2,k))
			{
				exch(k/2,k);
				k = k/2;
			}
		}

		void sink(int k)
		{
			while(2*k<=N)
			{
				int j = 2*k;

				if(j<N && less(j,j+1))
					j++;

				if(less(j,k))
					break;

				exch(j,k);

				k = j;
			}
		}

	public :
		MaxPQ(int capacity)
		{
			pq = new char[capacity+1];
			N = 0;
			size = 0;
		}

		void insert(char key)
		{
			pq[++N] = key;
			size++;
			swim(N);
		}

		char delMax()
		{
			char max = pq[1];
			exch(1,N--);
			pq[N+1] = 0;
			size--;
			sink(1);
			return max;	
		}

		int topMax()
		{
			return pq[1];
		}

		bool isEmpty()
		{
			return size==0;
		}

		int sizePQ()
		{
			return size;
		}
};

int main()
{
	MaxPQ pq(11);
	char input;
	while(true)
	{
		cin>>input;
		if(input=='-')
			cout<<pq.delMax()<<endl;
		else
			pq.insert(input);
	}

	return 0;

}