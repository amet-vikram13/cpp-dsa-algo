#include <iostream>
#include <string>
using namespace std;

class SuffixArrays
{
	private:
		string* arr;
		int n;
		bool is_sorted;

		int charAtd(string key,int d)
		{
			if (d < key.size()) return key[d]-'a';
			return -1;
		}

		void exch(int i,int j)
		{
			string tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}

		void three_way_quicksort(int lo,int hi,int d)
		{
			if (lo >= hi) return;
			int lt = lo, gt = hi;
			int v = charAtd(arr[lo],d);
			int i=lo+1;
			while(i<=gt)
			{
				int t = charAtd(arr[i],d);
				if (v > t)      exch(lt++,i++);
				else if (v < t) exch(gt--,i);
				else            i++;
			}

			three_way_quicksort(lo,lt-1,d);
			if (v>=0) three_way_quicksort(lt,gt,d+1);
			three_way_quicksort(gt+1,hi,d);
		}

	public:
		SuffixArrays(string inp)
		{
			n = inp.size();
			arr = new string[n];
			for(int i=0;i<n;i++)
				arr[i] = inp.substr(i);
			is_sorted = false;
		}

		bool sorted()
		{	return is_sorted; }

		void sortSuffix()
		{
			three_way_quicksort(0,n-1,0);
			is_sorted = true;
		}

		void printSortedSuffixArray()
		{
			for(int i=0;i<n;i++)
				cout << arr[i] << " ";
			cout << endl;
		}
};

int main()
{
	string inp;
	cin >> inp;
	SuffixArrays sa(inp);
	sa.sortSuffix();
	sa.printSortedSuffixArray();
}