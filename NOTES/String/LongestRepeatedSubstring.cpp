#include <bits/stdc++.h>
using namespace std;

/*

Problem: Given a string of N characters, find the longest repeated substring.

Brute-force algorithm:
- Try all indices i and j for start of possible match.
- Compute longest common prefix (LCP) for each pair.
Analysis: Running Time <= D*N^2, where D is length of longest match.

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

		string* getSorted()
		{
			return a;
		}
};

class LongestRepeatedSubstring
{
	private:
		int N;
		string* suffixes;
		string lrs;

		int lcp(string a,string b)
		{
			int n = (a.size() < b.size()) ? a.size():b.size();

			for(int i=0;i<n;i++)
				if (a[i] != b[i]) return i;

			return n;
		}

	public:
		LongestRepeatedSubstring(string inp)
		{
			N = inp.size();
			suffixes = new string[N];

			for(int i=0;i<N;i++)
				suffixes[i] = inp.substr(i);

			ThreeWayQuickSort tqs(suffixes,N);

			lrs = "";
			int len;
			for(int i=0;i<N-1;i++)
			{
				len = lcp(suffixes[i],suffixes[i+1]);
				if (len > lrs.size())
					lrs = suffixes[i].substr(0,len);
			}
		}

		string giveLRS()
		{	return lrs; }
};

int main()
{
	string inp;
	getline(cin,inp);
	LongestRepeatedSubstring lrs(inp);
	cout << lrs.giveLRS() << endl;
	return 0;
}