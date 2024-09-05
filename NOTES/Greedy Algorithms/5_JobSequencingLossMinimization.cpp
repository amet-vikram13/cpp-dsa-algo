#include <bits/stdc++.h>
using namespace std;

/*
Let us consider two extreme cases and we shall deduce the general case solution from them :-

1) All jobs take same time to finish, i.e Ti = k for all i. Since all jobs take same time to 
   finish we should first select jobs which have large Loss (Li). We should select jobs which 
   have the highest losses and finish them as early as possible. Thus this is a greedy algorithm. 
   Sort the jobs in descending order based on Li only.

2) All jobs have the same penalty. Since all jobs have the same penalty we will do those jobs first 
   which will take less amount of time to finish. This will minimize the total delay, and hence also 
   the total loss incurred. This is also a greedy algorithm. Sort the jobs in ascending order based 
   on Ti. Or we can also sort in descending order of 1/Ti.

From the above cases, we can easily see that we should sort the jobs not on the basis of Li or Ti alone. 
Instead, we should sort the jobs according to the ratio Li/Ti, in descending order.

We can get the lexicographically smallest permutation of jobs if we perform a stable sort on the jobs. 
To compare a/b and c/d, compare ad and bc.

/* QUICK NOTE
Formally stability may be defined as,
Let A be an array, and let < be a strict weak ordering on the elements of A.
A sorting algorithm is stable if-
	i < j and A[i] = A[j] implies  pi(i) < pi(j)
where pi is the sorting permutation ( sorting moves A[i] to position pi(i) )
*/

struct Job
{
	int id,t,l;
};

bool comparision(Job a,Job b)
{
	int a_loss = a.l;
	int a_days = a.t;
	int b_loss = b.l;
	int b_days = b.t;
	return (a_loss*b_days > b_loss*a_days);
}

// Complexity : Time O(nlogn) Space O(n)
void printOptimal(int L[],int T[],int n)
{
	Job arr[n];

	for(int i=0;i<n;i++)
		arr[i] = {i+1,T[i],L[i]};

	stable_sort(arr,arr+n,comparision);

	for(int i=0;i<n;i++)
		cout<<arr[i].id<<" ";
	cout<<endl;
}

int main()
{
	int L[] = { 1, 2, 3, 5, 6 };
    int T[] = { 2, 4, 1, 3, 2 };
    int N = 5;
    printOptimal(L, T, N);
    return 0;
}