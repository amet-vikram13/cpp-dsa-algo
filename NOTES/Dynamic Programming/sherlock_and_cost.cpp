#include <bits/stdc++.h>
using namespace std;

// TAKEAWAY :- One Very important aspect of this DP ques that
//             we divided the dp array into two arrays H and L
//             and final answer for any index i is 
//             dp[i] = max(L[i],H[i])
//             L[i] - when A[i] is 1
//             H[i] - when A[i] is B[i]
//             And in both L and H they represent max_consecutive_difference_sum
//             and dp[i] gives the same overall

//			   According to question the elements of array
//             A can be 1 <= A[i] <= B[i] but to get tha max
//             consecutive difference A[i] can be only 1 or B[i];
//             Total number of possible arrays is 2^B.length

//             You can't just get correct solution by examining incomplete
//             set of subproblems you need to see all subproblems.

int cost(int* arr,int n)
{
	int* L = new int[n];
	int* H = new int[n];

	// L[i] -- max cost when A[i] element is 1 
	// H[i] -- max cost when A[i] element is B[i]
	// Both L & H should be of atleast 2 unit length

	// Length - 1 unit
	L[0] = 0;
	H[0] = 0;

	L[1] = max(arr[0]-1,0);
	H[1] = max(arr[1]-1,arr[1]-1);

	int L_a,L_b,H_a,H_b;

	for(int i=2;i<n;i++)
	{
		// When the current element is 1 then previous element can be 1 or B[i];
		L_a = arr[i-1]-1 + H[i-1];
		L_b = L[i-1];

		L[i] = max(L_a,L_b);

		// When current is B[i] then previous element can be 1 or B[i]
		H_a = arr[i]-1 + L[i-1];
		H_b = arr[i]-arr[i-1] + H[i-1];

		H[i] = max(H_a,H_b);
	}

	return max(L[n-1],H[n-1])
}

int main()
{
	int t,n;
	cin>>t;

	while(t--)
	{
		cin>>n;
		int* arr = new int[n];

		for(int i=0;i<n;i++)
			cin>>arr[i];

		cout<<cost(arr,n)<<endl;

	}

	return 0;
}
