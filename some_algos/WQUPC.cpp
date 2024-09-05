#include <iostream>
using namespace std;

class Connectivity
{
	private :
		int * id;
		int * sz;
		int components;

	public :
		Connectivity(int N)
		{
			components = N;
			id = new int[N];
			sz = new int[N];
			
			for(int i=0;i<N;i++)
			{
				id[i] = i;
				sz[i] = 1;
			}
		}

		int count()
		{ return components; }

		int root(int i)
		{
			while(i!=id[i])
			{
				id[i] = id[id[i]];
				i = id[i];
			}

			return i;
		}

		bool isConnected(int p,int q)
		{ 
			return root(p)==root(q); 
		}

		void connect(int p,int q)
		{
			int proot = root(p);
			int qroot = root(q);
			if(sz[p] > sz[q])
			{
				id[qroot] = proot;
				sz[p] += sz[q];
				components--;
			}
			else
			{
				id[proot] = qroot;
				sz[q] += sz[p];
				components--;
			}
		}

};

int main()
{
 	Connectivity qu(10);
 	qu.connect(2,8);
 	cout<<qu.isConnected(2,8)<<" "<<qu.count()<<endl;

}