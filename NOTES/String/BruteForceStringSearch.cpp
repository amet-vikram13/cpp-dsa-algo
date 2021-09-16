#include <bits/stdc++.h>
using namespace std;

class BruteForceStringSearch
{
	private:
		int M;
		int N;
		int idx;

		void search(string pat,string txt)
		{
			for(int i=0;i<=N-M;i++)
			{
				int j;
				
				for(j = 0;j<M;j++)
				{
					if (txt[i+j] != pat[j])
						break;
				}
				
				if (j == M)
				{
					idx = i;
					return;
				}
			}

			idx = N;
		}

		void bufferSearch(string pat,string txt)
		{
			int i,j;
			for(i=0,j=0;i<N && j<M;i++)
			{
				//cout << "i: " << i << " j: " << j << endl;
				if   (txt[i] == pat[j]) j++;
				else { i -= j; j=0; }
			}

			if   (j == M) idx = i-M;
			else          idx = N;

		}

	public:
		BruteForceStringSearch(string pat,string txt)
		{
			M = pat.size();
			N = txt.size();
			idx = -1;
			//search(pat,txt);
			bufferSearch(pat,txt);
		}

		int giveIndex()
		{	return idx; }
};

int main()
{
	BruteForceStringSearch bfs("ABRA","ABACADABRAC");
	cout << bfs.giveIndex() << endl;
}