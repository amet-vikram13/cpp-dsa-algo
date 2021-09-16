#include <iostream>
#include <iomanip>
#include <functional>
#include <queue>
using namespace std;

priority_queue<int> max_heap_left;
priority_queue<int,vector<int>,greater<int> > min_heap_right;

void calculate_median(double x,double &median)
{
	if     (max_heap_left.size()==min_heap_right.size())
	{
		if     (x >= median)
		{
			min_heap_right.push(x);
			median = (double) min_heap_right.top();
		}
		else if(x < median)
		{
			max_heap_left.push(x);
			median = (double) max_heap_left.top();
		}
	}

	else if(min_heap_right.size() > max_heap_left.size())
	{
		if     (x > median)
		{
			max_heap_left.push(min_heap_right.top());
			min_heap_right.pop();
			min_heap_right.push(x);
		}
		else if(x <= median)
			max_heap_left.push(x);

		median = ((double)max_heap_left.top()+(double)min_heap_right.top())/2.0;

	}

	else if(max_heap_left.size() > min_heap_right.size())
	{
		if     (x < median)
		{
			min_heap_right.push(max_heap_left.top());
			max_heap_left.pop();
			max_heap_left.push(x);
		}
		else if(x >= median)
			min_heap_right.push(x);

		median = ((double)max_heap_left.top()+(double)min_heap_right.top())/2.0;
	}
}


int main()
{
	int t,x; cin>>t;
	double median = 0;
	while(t--)
	{
		cin>>x;
		calculate_median(x,median);
		cout<<fixed<<setprecision(1)<<median<<endl;
		
	}
	return 0;
}

