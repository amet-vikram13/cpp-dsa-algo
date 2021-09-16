#include <iostream>
#include <cstdlib>
using namespace std;

class MaxPQ
{
	private:
		int N;
		int size;
		int capacity;
		int* pq;
		int* qp;
		int  qp_i;

		bool more (int i,int j)
		{	return pq[i] > pq[j]; }

		void exch (int i,int j)
		{
			int temp = pq[i];
			pq[i] = pq[j];
			pq[j] = temp;
		}

		void swim(int k)
		{
			while(k>1 && more(k,k/2))
			{
				exch(k,k/2);
				k = k/2;
			}
		}

		void sink(int k)
		{
			while(2*k <= N)
			{
				int j = 2*k;

				if(j<N && more(j+1,j))
					j++;

				if (more(k,j))
					break;

				exch(k,j);

				k = j;
			}
		}

		void _insert(int key)
		{
			pq[++N] = key;
			size++;
			swim(N);
		}

	public:
		MaxPQ(int s,int n)
		{
			qp_i = 0;
			qp = new int[n-s];
			pq = new int[s+1];
			for(int i=0;i<=s;i++)
				pq[i] = -1;
			capacity = s;
			N = 0;
			size = 0;
		}

		void insert(int key)
		{
			if (N != capacity)
				_insert(key);
			else
			{
				if (key < topMax())
				{
					delMax();
					_insert(key);
				}
			}
		}

		void delMax()
		{
			qp[qp_i++] = pq[1];
			exch(1,N--);
			pq[N+1] = -1;
			size--;
			sink(1);
		}

		int sizePQ() { return size; }

		bool isEmpty() { return size==0; }

		int topMax() { return pq[1]; }

		int* givePQ() { return pq; }

		int* giveQP() { return qp; }
};


int fair_cut(int* arr,int n,int k)
{
	MaxPQ* pq = new MaxPQ(k,n);

	for (int i=0;i<n;i++)
		pq->insert(arr[i]);


	int* lin = pq->givePQ();
	int* lu  = pq->giveQP();

	for (int i=1;i<=k;i++)
		cout << lin[i] << " ";
	cout << endl;

	for (int i=0;i<n-k;i++)
		cout << lu[i] << " ";
	cout << endl;

	int summ=0;

	for(int i=1;i<=k;i++)
	{
		for(int j=0;j<n-k;j++)
			summ += abs(lu[j]-lin     [i]);
	}

	return summ;
}



int main()
{
	int n,k;
	cin >> n >> k;

	int* arr = new int[n];

	for(int i=0;i<n;i++)
		cin >> arr[i];

	cout << fair_cut(arr,n,k) << endl;

	return 0;
}