#include <bits/stdc++.h>
using namespace std;

struct Job
{
	int start;
	int finish;
	int profit;
};

bool less_job(Job x,Job y)
{
	return (x.finish < y.finish);
}

int firstNonConflictFromRight(Job* arr,int i)
{
	for(int j=i-1;j>-1;j--)
	{
		if (arr[j].finish <= arr[i].start)
			return j;
	}
	return -1;
}

int findMaxProfit(Job* arr,int n)
{
	sort(arr,arr+n,less_job);

	int* dp = new int[n];
	dp[0] = arr[0].profit;

	for(int i=1;i<n;i++)
	{
		int curr_profit = arr[i].profit;
		int l = firstNonConflictFromRight(arr,i);
		if (l!=-1)
			curr_profit += dp[l];

		dp[i] = max(curr_profit,dp[i-1]);
	}

	return dp[n-1];
}

int main()
{
	int n,s,e,p;
	cin >> n;
	Job* arr = new Job[n];
	int i=0;
	while(i<n)
	{
		cin >> s >> e >> p;
		arr[i].start = s;
		arr[i].finish = e;
		arr[i].profit = p;
		i++;
	}
	cout << findMaxProfit(arr,n) << endl;
	return 0;

}