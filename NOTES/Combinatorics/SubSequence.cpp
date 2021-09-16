#include <iostream>
#include <vector>
using namespace std;

// Subsequence
/* A subsequence is a sequence that can be derived from another sequence by zero or more elements, 
without changing the order of the remaining elements. For the same example, there are 15 sub-sequences for sequence (1,2,3,4),
they are (1), (2), (3), (4), (1,2), (1,3),(1,4), (2,3), (2,4), (3,4), (1,2,3), (1,2,4), (1,3,4), (2,3,4), (1,2,3,4). 
More generally, we can say that for a sequence of size n, we can have (2^n-1) non-empty sub-sequences in total i.e a total
of 2^n sequences all together know as Power Set of sequence.

Consider Example [1,2,3] then all its 2^3=8 subsets are bitmasked as :-

000 - Empty set
	  0 for 3 j=2 001
	  0 for 2 j=1 010
	  0 for 1 j=0 100

001 - 3
	  1 for 3 j=2 001
	  0 for 2 j=1 010
	  0 for 1 j=0 100

010 - 2
	  0 for 3 j=2 001
	  1 for 2 j=1 010
	  0 for 1 j=0 100

100 - 1
	  0 for 3 j=2 001
	  0 for 2 j=1 010
	  1 for 1 j=0 100

011 - 3 2
	  1 for 3 j=2 001
	  1 for 2 j=1 010
	  0 for 1 j=0 100

101 - 1 3
	  1 for 3 j=2 001
	  0 for 2 j=1 010
	  1 for 1 j=0 100

110 - 2 1
	  0 for 3 j=2 001
	  1 for 2 j=1 010
	  1 for 1 j=0 100

111 - 1 2 3
	  1 for 3 j=2 001
	  1 for 2 j=1 010
	  1 for 1 j=0 100
*/

// Complexity : Time O(n*(2^n)) Space O(1)
void subSequence(int arr[],int n)
{
	for(int i=0;i<(1<<n);i++) // Subset code
	{
		for(int j=0;j<n;j++) // element code
		{
			if((1<<j) & (i))
				cout<<arr[j]<<" ";
		}
		cout<<endl;
	}
}

// Sum of all subsequences
/* Method 1

When you generate the sequence code you can see that
every element occurs only only half of the time 
i.e 2^n/2 = 2^(n-1) times. Consider example :-

arr = [1,2,3] consider only for number 3 (code : 001)

000,100,010,<001>,110,<101>,<011>,<111> 

*/

int sumSubSequence(int arr[],int n)
{
	int sum = 0;
	for(int i=0;i<n;i++)
		sum += arr[i];
	return ((1<<n)*sum);
}

// Finding length of Longest Increasing Subsequence (LIS)
/*
arr[]	10	22	9	33	21	50	41	60	80
LIS		1	2		3		4		5	6

Let arr[0...n-1] be the input array and L(i) be the length of 
the LIS ending at index i such that arr[i] is the last element of
LIS.

L(i) can be recursively written as:-
	
	L(i) = 1 + max( L(j) ) where 0 < j < i and arr[j] < arr[i]; 
	or
	L(i) = 1, if no such j exists;

To find the LIS for a given array, we need to return 
max(L(i)) where 0 < i < n.


Method 1 (Recursive implementation of the LIS problem)
		
EX : array of size 4		
	      
	      lis(4) --- lis(1)
        /     \     
      lis(3)  lis(2) 
     /          \
   lis(2) 	  lis(1)
   /
lis(1)
*/

//Complexity : Time O(n^2)
int _lis(int arr[],int n,int * max_ref)
{
   /* 
   To make use of recursive calls, this function must return
   two things:
   
   1) Length of LIS ending with element arr[n-1]. We use
      max_ending_here for this purpose
   
   2) Overall maximum as the LIS may end with an element
      before arr[n-1] max_ref is used this purpose.
   
   The value of LIS of full array of size n is stored in
   *max_ref which is our final result 
   */

	// Base Case
	if(n==1)
		return 1;

	// 'max_ending_here' is length of LIS ending with arr[n-1]
	int res = 0,max_ending_here = 1;

	/* Recursively get all LIS ending with arr[0], arr[1] ...
       arr[n-2]. If   arr[i-1] is smaller than arr[n-1], and
       max ending with arr[n-1] needs to be updated, then
       update it 
    */
	for(int i=1;i<n;i++)
	{
		res = _lis(arr,i,max_ref);
		// Here 1 signifies the last element arr[n-1]
		// thus, LIS ending at arr[i] together with last
		// element.
		if(arr[i-1]<arr[n-1] && res+1 > max_ending_here)
			max_ending_here = res+1;
	}

	// Compare max_ending_here with the overall max. And
    // update the overall max if needed
	if(*max_ref < max_ending_here)
		*max_ref = max_ending_here;

	// Return length of LIS ending with arr[n-1]
	return max_ending_here;
}
// The wrapper function for _lis()
int rlis(int arr[], int n)
{
    // The max variable holds the result
    int max = 1;
 
    // The function _lis() stores its result in max
    _lis( arr, n, &max );
 
    // returns max
    return max;
}

// Method 2 (Array Implementation)
//Complexity : Time O(n^2)
int alis(int arr[],int n)
{
	/* lis() returns the length of the longest increasing
 	 subsequence in arr[] of size n */
	
	int * lisarr = new int[n];
	int i,j,max = 0;

	/* Initialize LIS values for all indexes */
	for(i=0;i<n;i++)
		lisarr[i] = 1;

	/* Compute optimized LIS values in bottom up manner */
	for(i=1;i<n;i++)
		for(j=0;j<i;j++)
			if(arr[i]>arr[j] && lisarr[i]<lisarr[j]+1)
				lisarr[i] = lisarr[j]+1;

	for(i=0;i<n;i++)
		if(max<lisarr[i])
			max = lisarr[i];

	delete [] lisarr;

	return max;
}

/* Method 3 - https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
*/


// Constructing Longest Increasing Subsequence
/*
Input:  [10, 22, 9, 33, 21, 50, 41, 60, 80]
Output: [10, 22, 33, 50, 60, 80] 
OR [10 22 33 41 60 80] or any other LIS of same length.

Let arr[0..n-1] be the input array. We define vector L such that L[i] is 
itself is a vector that stores LIS of arr that ends with arr[i]. 
For example, for array [3, 2, 6, 4, 5, 1],

L[0]: 3
L[1]: 2
L[2]: 2 6
L[3]: 2 4
L[4]: 2 4 5
L[5]: 1
Therefore for an index i, L[i] can be recursively written as –

L[0] = {arr[O]}
L[i] = {Max(L[j])} + arr[i] 
where j < i and arr[j] < arr[i] and if there is no such j then L[i] = arr[i]

Method 1 (Using LIS and DP solution)
*/

//Complexity : Time O(n^2)
vector<int>& constructLis(int arr[],int n)
{
	// L[i] - The longest increasing sub-sequence 
    // ends with arr[i].
    vector<vector<int> >L(n);	

    //L[0] is equal to {arr[0]}
    L[0].push_back(arr[0]);

    for(int i=1;i<n;i++)
    {
    	for(int j=0;j<i;j++)
    	{
    		/* L[i] = {Max(L[j])} + arr[i]
            where j < i and arr[j] < arr[i] */
            if(arr[i]>arr[j] && L[i].size() < L[j].size()+1)
            	L[i] = L[j];	
    	}

    	// L[i] ends with arr[i]
    	L[i].push_back(arr[i]);
    }

    // L[i] now stores increasing sub-sequence of
    // arr[0..i] that ends with arr[i]
    vector<int> max = L[0];

	for (vector<int> x : L)
    	if (x.size() > max.size())
        	max = x;

    return max;
}

/* Method 2 - https://www.geeksforgeeks.org/construction-of-longest-monotonically-increasing-subsequence-n-log-n/
*/


/* Counting all increasing subsequences

Input : arr[] = {1, 2, 3, 4}
Output: 15
There are total increasing subsequences
{1}, {2}, {3}, {4}, {1,2}, {1,3}, {1,4}, 
{2,3}, {2,4}, {3,4}, {1,2,3}, {1,2,4}, 
{1,3,4}, {2,3,4}, {1,2,3,4}


https://www.geeksforgeeks.org/count-all-increasing-subsequences/

*/