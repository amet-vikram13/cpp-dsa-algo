#include <bits/stdc++.h>
using namespace std;

// NOTE -- Very important concept of active lists and patient sorting
// Basically we keep track of subsequences' end element only
// mapped with their length. So, 
// tail[i] = j means subseqeunce length i with end element j;
int binary_search(int* tail,int l,int r,int key)
{
	while (r - l > 1)
	{
		int m = l + (r-l)/2 ;

		if (tail[m] >= key)
			r = m;
		else
			l = m;
	}

	return r;
}

int lonest_increasing_subsequence_active_list(int* arr,int n)
{
	if ( n == 0)
		return 0;

	int* tail = new int[n];
	tail[0] = v[0];   // Smallest element in tail
	int length = 1;   // Points toward empty slot in tail

	for(int i=1;i<n;i++)
	{
		// New smallest Value
		if (v[i] < tail[0])
			tail[0] = v[i];

		// v[i] extends an existing subsequence with largest end element
		else if (v[i] > tail[length-1])
			taile[length++] = v[i];


		// v[i] will become end candidate for an
		// existing subsequence some length and 
		// replace the previous one
		else
			tail[binary_search(tail,-1,length-1,v[i])] = v[i];
	}

	return length;
}

int main()
{
    int n;
    cin >> n;

    int* arr = new int[n];

    for (int i=0;i<n;i++)
        cin >> arr[i];

    cout << lonest_increasing_subsequence_active_list(arr,n) << endl;
    return 0;
}
