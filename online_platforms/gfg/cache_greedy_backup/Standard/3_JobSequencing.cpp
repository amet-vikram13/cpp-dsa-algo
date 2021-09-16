#include <bits/stdc++.h>
using namespace std;

/*
Given an array of jobs where every job has a deadline and associated profit if the job is finished 
before the deadline. It is also given that every job takes single unit of time, so the minimum possible 
deadline for any job is 1. How to maximize total profit if only one job can be scheduled at a time.

Examples:

Input: Four Jobs with following deadlines and profits
  JobID    Deadline      Profit
    a        4            20   
    b        1            10
    c        1            40  
    d        1            30
Output: Following is maximum profit sequence of jobs
        c, a   


Input:  Five Jobs with following deadlines and profits
   JobID     Deadline     Profit
     a         2           100
     b         1           19
     c         2           27
     d         1           25
     e         3           15
Output: Following is maximum profit sequence of jobs
        c, a, e

NOTE VIP : We could schedule Job a from 0-1 sec or 1-2 sec but we will
		   try to schedule our best job as late as possible. Also scheduling 
		   it earlier could prevent another more profitable job from being done
		   Therefore a is scheduled between 1-2 sec.

1) Sort all jobs in decreasing order of profit.
2) Initialize the result sequence as first job in sorted jobs.
3) Do following for remaining n-1 jobs
       a) If the current job can fit in the current result sequence 
          without missing the deadline, add current job to the result.
          Else ignore the current job.
*/

// a structure to represent a job
struct Job
{
	char id;
	int dead;
	int profit;
};

// utility function to sort jobs according to profit
bool comparision(Job a,Job b)
{
	return (a.profit > b.profit);
}

// Complexity : Time O(n^2)
// Returns minimum number of platforms reqquired
void printJobScheduling(Job arr[],int n)
{
	// Sort all jobs according to decreasing order of prfit
	sort(arr,arr+n,comparision);

	int result[n]; // To store result (Sequence of jobs)
	bool slot[n];  // To keep track of free time slots

	for(int i=0;i<n;i++)
		slot[i] = false;

	// Iterate through all given jobs
	for(int i=0;i < n;i++)
	{
		// Find a free slot for this job (Note that we start
        // from the last possible slot)
		for(int j = min(j,arr[i].dead)-1;j>-1;j--)
		{
			// Free slot found
			if(slot[j] == false)
			{
				result[j] = i;   // Add this job to result
				slot[j] = true;  // Make this slot occupied
				break;
			}
		}
	}

	
}

int main()
{
	Job arr[] = { {'a', 2, 100}, {'b', 1, 19}, {'c', 2, 27}, {'d', 1, 25}, {'e', 3, 15}};
	int n = 5;
	printJobScheduling(arr,n);
	return 0;
}