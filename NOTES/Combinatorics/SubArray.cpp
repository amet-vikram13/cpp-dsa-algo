#include <iostream>
#include <map>
using namespace std;

// 1. Subarray
/*
A subbarray is a contiguous part of array. An array that is inside another array. 
For example, consider the array [1, 2, 3, 4], There are 10 non-empty sub-arrays. 
The subbarays are (1), (2), (3), (4), (1,2), (2,3), (3,4), (1,2,3), (2,3,4) and (1,2,3,4). 
In general, for an array/string of size n, there are n*(n+1)/2 non-empty subarrays/subsrings.

For Array of Size n, if you want to select :-
1) 1 element then C(n,1) options ## [1],[2],[3],....,[n]
2) 2 element then C(n-1,1) options ## [1,2],[2,3],.....[n-1,n]
3) 3 element then C(n-2,1) options $$ [1,2,3],[2,3,4]......[n-2,n-1,n]
4) n-1 element then C(2,1)
5) n element then 1

Therefore no of options = 1+C(2,1)+C(3,1)+C(4,1)+..C(n-1,1)+C(n,1) = C(n+1,2) = C(n,2)+n
## Just convert 1 = C(2,2) and use C(n,r)+C(n,r+1=C(n+1,r+1)
*/

// Complexity : Time O(n^2) Space O(1) 
void subArray(int arr[],int n)
{
	// Pick a starting point
	for(int i=0;i<n;i++)
	{
		// Pick a ending point
		for(int j=i;j<n;j++)
		{
			// print subarray between starting
			// and ending point
			for(int k=i;k<=j;k++)
				cout<<arr[k]<<" ";

			cout<<endl;
		}
	}
}

// 2. Sum of all Subarrays
/*
Method 1 (Simple Solution)

A simple solution is to generate all sub-array and compute their sum.
Complexity : Time O(n^2) Space O(1)

Method 2 (Efficient Solution)

Consider example arr = [1,2,3] :-

Every element arr[i] appears in two types of subsets:

i)  In subarrays beginning with arr[i]. There are 
    (n-i) such subsets. For example [2] appears
    in [2] and [2, 3].

ii) In (n-i)*i subarrays where this element is not
    first element. For example [2] appears in 
    [1, 2] and [1, 2, 3].

Total appearance of arr[i] = (n-i)+(n-i)*i

{x0,x1,x2,x3,.....,x(n-1)}

   x0     		| x2				| x(n-1)
 		  		|					|
 x1,x2    		|x2,x3				|
		  		|					|
x1,x2,x3  		|x2,x3,x4			|
	.			|    .				|
	.			|	 .				|
	.			|	 .				|
#n - first		|#(n-2) - first		| #1 - first 
#0 - inbetween	|#(n-2)*2 - inbetween #(n-(n-1))*(n-1) - inbetween

*/
// Complexity : Time O(n) Space O(1)
int sumSubArray(int arr[],int n)
{
	int result = 0;
	for(int i=0;i<n;i++)
		result += arr[i]*(n-i)*(i+1);
	return result
}


//3. Finding number of arrays with XOR given as value m

/* Method 1 (Simple solution)
Generate all subarrays and keep checking the XOR.

Complexity : Time O(n^2) Space O(1)

Method 2 (Efficient)

Let us call the XOR of all elements in the range [i+1, j] as A, in the range [0,i] as B, and in the range [0,j] as C. 
If we do XOR of B with C, the overlapping elements in [0,i] from B and C zero out and we get XOR of all elements in the range [i+1,j], 
i.e. A. Since A = B XOR C, we have B = A XOR C.

		B 					  A
[0................i][i+1................j]
[0......................................j]
					C

Now Our desired subsequence is A whose XOR is m so we get the count of A as the count of all B satisfying this relation.

1) Compute xorArr, the prefix xor array. (i.e xorArr[i] = Arr[0]^Arr[1]^Arr[2]^...Arr[i])
2) Create a map mp in which we store count of all prefixes with XOR or all visited XOR as a particular value. 

Complexity : Time O(n) Space O(1)
*/

long long int subXorArr(int arr[],int n,int m)
{
	int ans = 0;

	int * xorArr = new int[n];

	xorArr[0] = arr[0];

	for(int i=0;i<n;i++)
		xorArr[i] ^= arr[i];

	map<int,int> visitedXor;

	for(int i=0;i<n;i++)
	{
		int temp = m^xorArr[i];

		// If above XOR exists in map, then there
        // is another previous prefix with same
        // XOR, i.e., there is a subarray ending
        // at i with XOR equal to m.
		ans += visitedXor[temp];

		if(temp==m)
			ans++;

		// Add the XOR of this subarray to the map
		visitedXor[xorArr[i]]++;
	}
}