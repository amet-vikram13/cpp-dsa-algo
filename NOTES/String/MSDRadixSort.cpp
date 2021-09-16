#include <bits/stdc++.h>
using namespace std;

/*

MSD Radix Sort :
- Partition array into R pieces according to first character. (Use Counting Sort)
- Recursively sort all strings that start with each character 
  (Counting Sort delineate subarrays to sort)

Observation 1 : Much too slow for small subarrays.
- Each function call needs its own count[] array.

Observation 2 : Huge number of small subarrays because of 
                recursion

Solution : Coutoff to insertion sort for small subarrays.
- Insertion sort, but start at dth character.
- implement less() so that it compares starting at dth character.

Number of characters examined :
- MSD examines just enough characters to sort the keys.
- Numeber of characters examined depends on keys.
- Can be sublinear in input size.

Time Complexity : 
gurantee - 2*N*W
random   - N*logR(N)
extra space - N + DR (D - function call stack depth)
stable - yes

Disadvantages :
- Access memory randomly (cache inefficient).
- Inner loop has a lot of instructions.
- Extra space for count.
- Extra space for aux.

*/

class MSDRadixSort
{
	private:
		int R;
		string* aux;
		int* count;
		string* a;
		int N;

		int charAtd(string str,int d)
		{
			if (d < str.size()) return (int(str[d])-int('a')+1);
			else return -1; 
		}

		void msdSort(int lo,int hi,int d)
		{
			if (hi <= lo) return;

			
			//cout << "lo: " << lo << " hi: " << hi << " d: " << d << endl;

			// Now in this case,
			// if space of characters is from 1...R i.e R characters
			// then we need count from 1....R+2 i.e C array of length R+3.
			count = new int[R+3];
			for(int i=0;i<R+3;i++)
				count[i] = 0;

			
			// Here unlike simple counting sort, the motive is 
			// NOT make a count array s.t count[r] represents all the
			// number of characters less than character chr(r) s.t it gives the
			// starting position of chr(r) in aux array.
			// Here the motive is to make a count array s.t it represents a range of characters
			// with same character in chr(r) in aux array. For eg see below.
			for(int i=lo;i <= hi; i++)
				count[charAtd(a[i],d) + 2]++;

			/*
			for(int i=0;i<R+3;i++)
				cout << count[i] << " ";
			cout << endl;
			*/

			for(int r=0;r < R+2; r++)
				count[r+1] += count[r];
			/*
			Count array for d:1.
			count array: 0 0 0 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 12 14 14 14 14 14 14 14

			Now count[r+1] gives starting positions for chr(r).
			*/
			/*
			for(int i=0;i<R+3;i++)
				cout << count[i] << " ";
			cout << endl;
			*/
			

			for(int i=lo;i <= hi;i++)
				aux[count[charAtd(a[i],d) + 1]++] = a[i];
			/*
			count array: 0 0 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 12 14 14 14 14 14 14 14 14
			Now finally count[r] and count[r]-1 gives range of character for chr(r).
			i: 0 - are
			i: 1 - by
			i: 2 - she
			i: 3 - sells
			i: 4 - seashells
			i: 5 - sea
			i: 6 - shore
			i: 7 - shells
			i: 8 - she
			i: 9 - sells
			i: 10 - surely
			i: 11 - seashells
			i: 12 - the
			i: 13 - the
			*/

			/*
			for(int i=0;i<R+3;i++)
				cout << count[i] << " ";
			cout << endl;

			for(int i=0;i<N;i++)
			{
				cout << "i: " << i << " - " << aux[i] << endl;
			}
			*/

			for(int i=lo;i <= hi; i++)
				a[i] = aux[i - lo];

			for(int r=0; r < R+1; r++)
				msdSort(lo+count[r],lo+count[r+1]-1,d+1);
		}

	public:
		MSDRadixSort(string* inp,int n)
		{
			N = n;
			R = 26; // space of characters from 1 to 26.
			a = inp;
			aux = new string[N];
			msdSort(0,N-1,0);
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
	MSDRadixSort rdx(inp,14);
	rdx.printSorted();
	return 0;
}
