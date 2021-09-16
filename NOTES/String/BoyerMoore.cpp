#include <bits/stdc++.h>
using namespace std;

/*

Intutuion: Scan characters in pattern from right to left.
         : Can skip as many M text chars when finding one not in pattern

Property: Substring search with the Boyre-Moore mismatched character heuristic
          takes about ~ N / M character compares to search for a pattern of length
          M in a text of length N.

Worst Case: Can  be bad as ~ MN.
*/

class BoyreMoore
{
	private:
		int M;
		int R;
		string pat;
		int* right;

		int charAt(char c)
		{	return int(c)-int('A'); }

	public:
		BoyreMoore(string pattern)
		{
			pat = pattern;
			M = pat.size();
			R = 26;
			right = new int[R];

			for(int i=0;i<R;i++)
				right[i] = -1;

			for(int i=0;i<M;i++)
				right[charAt(pat[i])] = i;
		}

		int search(string txt)
		{
			int N = txt.size();
			int skip;
			for(int i=0;i<=N-M;i+=skip)
			{
				skip = 0;
				for(int j=M-1;j>=0;j--)
				{
					
					/*
					cout << "i: " << i << " ";
					for(int k=0;k<N;k++)
						cout << txt[k] << " ";
					cout<<endl;
					if (i < 10)
						cout << "j: " << j << " ";
					else
						cout << "j: " << j << "  ";
					for(int k=0;k<i;k++)
						cout << " "  << " ";
					for(int k=0;k<M;k++)
						cout << pat[k] << " ";
					cout << endl << endl;
					*/

					if (pat[j] != txt[i+j])
					{
						skip = (1 > j-right[charAt(txt[i+j])]) ? 1 : j-right[charAt(txt[i+j])];
						break;
					}
				}

				if (skip == 0) return i;
			}
			return N;
		}
};

int main()
{
	BoyreMoore bm("NEEDLE");	
	cout << bm.search("FINDINAHAYSTACKNEEDLEINA") << endl;
	return 0;
	
}