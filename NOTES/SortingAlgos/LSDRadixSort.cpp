#include <bits/stdc++.h>
using namespace std;

/*
LSD string (radix) sort :
    * Consider characters from right to left
    * Stably sort the whole word using dth character as the key using counting sort

Proposition : LSD sorts fixed-length strings in ascending order

			: After pass i, strings are sorted by last i characters.

			: If two strings differ on sort key, counting sort puts them
			  in proper relative order

			: If two strings agree on sort key, stability keeps them in proper
			  relative order


Gurantee Time : 2*W*N
Randome  Time : 2*W*N
Extra space   : N+R
stable        : yes

(W: length of string, N: Number of strings, R: radix or space of characters)

What is the running time of Radix Sort?
Let there be d digits in input integers. Radix Sort takes O(d*(n+b)) time where b is the base for 
representing numbers, for example, for decimal system, b is 10. What is the value of d? If k is the 
maximum possible value, then d would be O(logb(k)). So overall time complexity is O((n+b) * logb(k)). 
Which looks more than the time complexity of comparison based sorting algorithms for a large k. Let 
us first limit k. Let k <= nc where c is a constant. In that case, the complexity becomes O(nLogb(n)). 
But it still doesn’t beat comparison based sorting algorithms.
What if we make value of b larger?. What should be the value of b to make the time complexity linear? 
If we set b as n, we get the time complexity as O(n). In other words, we can sort an array of integers 
with range from 1 to nc if the numbers are represented in base n (or every digit takes log2(n) bits).

Is Radix Sort preferable to Comparison based sorting algorithms like Quick-Sort?
If we have log2n bits for every digit, the running time of Radix appears to be better than Quick Sort for 
a wide range of input numbers. The constant factors hidden in asymptotic notation are higher for Radix Sort 
and Quick-Sort uses hardware caches more effectively. Also, Radix sort uses counting sort as a subroutine 
and counting sort takes extra space to sort numbers.
*/

class LSDRadixSort
{
	private:
		int R;  // space of integers 0..9
		int* count;
		string* aux;
		int W;       // fixed length strings
		int N;       // length of array of strings


	public:
		LSDRadixSort(string* a,int n,int w)
		{
			R = 11;
			N = n;
			W = w;
			aux   = new string[N];
			count = new int[R];

			for(int d=W-1;d>-1;d--)
			{
				for(int i=0;i<R;i++)
					count[i] = 0;
				for(int i=0;i<N;i++)
					count[int(a[i][d]-'0')+1]++;
				for(int i=0;i<R-1;i++)
					count[i+1] += count[i];
				for(int i=0;i<N;i++)
					aux[count[int(a[i][d]-'0')]++] = a[i];
				for(int i=0;i<N;i++)
					a[i] = aux[i];
			}

			for(int i=0;i<N;i++)
				cout << a[i] << " ";
			cout << endl;  
		}

};


int main()
{
	string a[] = {"234","674","864","346","732","133","476","436","265","350"};
	LSDRadixSort lsd(a,10,3);
	return 0;	
}