#include <bits/stdc++.h>
using namespace std;

/*

https://en.wikipedia.org/wiki/Activity_selection_problem

You are given n activities with their start and finish times. Select the maximum number of 
activities that can be performed by a single person, assuming that a person can only work 
on a single activity at a time.

Example 1 : Consider the following 3 activities sorted by
by finish time.
     start[]  =  {10, 12, 20};
     finish[] =  {20, 25, 30};

A person can perform at most two activities. The 
maximum set of activities that can be executed 
is {0, 2} [ These are indexes in start[] and 
finish[] ]

Example 2 : Consider the following 6 activities 
sorted by by finish time.
     start[]  =  {1, 3, 0, 5, 8, 5};
     finish[] =  {2, 4, 6, 7, 9, 9};

A person can perform at most four activities. The 
maximum set of activities that can be executed 
is {0, 1, 3, 4} [ These are indexes in start[] and 
finish[] ]
 
###### IMP ######
The greedy choice is to always pick the next activity whose finish time is least among the remaining 
activities and the start time is more than or equal to the finish time of previously selected activity. 
We can sort the activities according to their finishing time so that we always consider the next activity 
as minimum finishing time activity.
#################

1) Sort the activities according to their finishing time
2) Select the first activity from the sorted array and print it.
3) Do following for remaining activities in the sorted array.
		a) If the start time of this activity is greater than or equal to the finish time 
		of previously selected activity then select this activity and print it.

*/

// Complexity : Time O(n)
void printMaxActivities(int s[],int f[],int n)
{
	/*
	Activity selection problem assuming 
	that they are sorted according to 
	finish time
	*/

	int i,j;

	// The first activity always gets selected
	i = 0;
	cout<<i<<" ";

	// Consider rest of the activities
	for(j = 1;j < n;j++)
	{
		// If this activity has start time greater than or
      	// equal to the finish time of previously selected
      	// activity, then select it
		if(s[j] >= f[i])
		{
			i = j;
			cout<<i<<" ";
		}
	}
	cout<<endl;
}

struct activity
{
	int start;
	int finish;
};

// utility function to print
void printArray(activity * arr,int n)
{
	for (int i = 0;i < n;i++)
		cout<<"("<<arr[i].start<<","<<arr[i].finish<<"), ";
	cout<<endl;
}

int randomPartition(activity * arr,int p,int r)
{
	// choosing a random index between p and r
	int random = p + rand()%(r-p+1);

	// making the element at random index as pivot
	activity temp  = arr[random];
	arr[random]    = arr[r];
	arr[r]         = temp;
	activity pivot = arr[r];

	int i = p-1;
	int j;

	// partitioning array in four zones
	// 1. p to i-1   ->  < pivot
	// 2. i to j-1   ->  > pivot
	// 3. j to r-1   ->  unprocessed
	// 4. r          ->  pivot
	for(int j = p;j < r;j++)
	{
		if (arr[j].finish <= pivot.finish)
		{
			i++;
			temp   = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	
	temp     = arr[r];
	arr[r]   = arr[i+1];
	arr[i+1] = temp;

	return i+1;
}
void _randomQuicksort(activity * arr,int p,int r)
{
	if (p < r) // stopping condition
	{
		int partition = randomPartition(arr,p,r);
		_randomQuicksort(arr,p,partition-1);
		_randomQuicksort(arr,partition+1,r);
	}
}
void randomQuicksort(activity * arr,int n)
{
	_randomQuicksort(arr,0,n-1);
	//printArray(arr,n);
}

// Complexity : Time O(nlgn)
void unsortedPrintMaxActivities(activity arr[], int n)
{
    /*
    Returns count of the maximum set of activities that can
    be done by a single person, one at a time.
	*/
	
    // Sort jobs according to finish time
    randomQuicksort(arr,n);
 
 	// The first activity always gets selected
    int i = 0;
    cout << "(" << arr[i].start << "," << arr[i].finish << "), ";
 
    // Consider rest of the activities
    for (int j = 1; j < n; j++)
    {
      // If this activity has start time greater than or
      // equal to the finish time of previously selected
      // activity, then select it
      if (arr[j].start >= arr[i].finish)
      {
          cout << "(" << arr[j].start << "," << arr[j].finish << "), ";
          i = j;
      }
    }
    cout<<endl;
}






int main()
{
	int s[] =  {1, 3, 0, 5, 8, 5};
    int f[] =  {2, 4, 6, 7, 9, 9};
    printMaxActivities(s,f,6);

    activity arr[] = {{5, 9}, {1, 2}, {3, 4}, {0, 6},{5, 7}, {8, 9}};
    unsortedPrintMaxActivities(arr,6);

	return 0;
}