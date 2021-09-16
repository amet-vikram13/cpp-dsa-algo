#include <bits/stdc++.h>
using namespace std;

/*

Does 3-way partitioning at dth character.
- Less overhead than R-way partitioning in MSD string sort.
- Does not re-examine characters equal to the partitioning char
(But does re-examine characters not equal to the partitioning char).

Standard QuickSort
- Uses ~2*N*lnN string compares on average.
- Costly for keys with long common prefixes (and this is the most common case)

3-way string (radix) quicksort
- Uses ~2*N*lnN character compares on average for random strings.
- Avoids re-comparing long common prefixes.

MSD strig sort
- Is cache-inefficent.
- Too much memory storing count.
- Too much overhead reinitializing count[] and aux[]

3-way string quicksort
- Has a shorted inner loop.
- Is cache friendly.
- Is in-plcae.

Time Complexity :
- gurantee = random = 1.39*W*N*lgN
Extra space : logN + W
Stable = No.
*/


class ThreeWayQuickSort
{
	private:
		string* a;
		int N;

		int charAtd(string str,int d)
		{
			if (d < str.size()) return (int(str[d])-int('a')+1);
			else return -1;
		}

		void exch(int i,int j)
		{
			string tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
		}

		void stringQuickSort(int lo,int hi,int d)
		{
			if (hi <= lo) return;
			int lt = lo,gt = hi;
			int v = charAtd(a[lo],d);
			int i = lo+1;
			while(i <= gt)
			{
				int t = charAtd(a[i],d);
				if      (t < v) exch(lt++, i++);
				else if (t > v) exch(i, gt--);
				else            i++;
			}

			stringQuickSort(lo,lt-1,d);
			if (v >= 0) stringQuickSort(lt,gt,d+1);
			stringQuickSort(gt+1,hi,d);
		}


	public:
		ThreeWayQuickSort(string* inp,int n)
		{
			N = n;
			a = inp;
			stringQuickSort(0,N-1,0);
		}

		void printSorted()
		{
			for(int i=0;i<N;i++)
				cout << a[i] << endl;
			cout << endl;	
		}
};

int main()
{
	string inp[] = {"she","sells","seashells","by","the","sea","shore","the","shells","she","sells","are","surely","seashells"};
	ThreeWayQuickSort twqs(inp,14);
	twqs.printSorted();
	return 0;
}
