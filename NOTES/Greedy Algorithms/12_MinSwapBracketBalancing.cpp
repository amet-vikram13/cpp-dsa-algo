#include <bits/stdc++.h>
using namespace std;

/*
We can initially go through the string and store the positions of ‘[‘ in a vector say ‘pos‘. 
Initialize ‘p’ to 0. We shall use p to traverse the vector ‘pos’. We maintain a count of 
encountered ‘[‘ brackets. When we encounter a ‘[‘ we increase the count, and increase ‘p’ 
by 1. When we encounter a ‘]’ we decrease the count. If the count ever goes negative, this 
means we must start swapping. The element pos[p] tells us the index of the next ‘[‘. We 
increase the sum by pos[p] – i, where i is the current index. We can swap the elements in 
the current index and pos[p] and reset count to 0.
*/


// Function to calculate swaps required
long swapCount(char s[],int n)
{
    // Keep track of '['
    vector<int> pos;
    for (int i = 0; i < n; ++i)
        if (s[i] == '[')
        {
        	cout<<i<<" ";
        	pos.push_back(i);
        }
    cout<<endl;
 
    int count = 0; // To count number of encountered '['
    int p = 0;  // To track position of next '[' in  pos vector
    long sum = 0; // To store result
 
    for (int i = 0; i < n; ++i)
    {
        // Increment count and move p to next position
        if (s[i] == '[')
        {
            ++count;
            ++p;
        }
        else if (s[i] == ']')
            --count;
 
        // We have encountered an unbalanced part of string
        if (count < 0)
        {
            // Increment sum by number of swaps required
            // i.e. position of next '[' - current position
            sum += pos[p] - i;
            swap(s[i], s[pos[p]]);
            ++p;
 
            // Reset count to 1
            count = 1;
        }
        cout<<"i:"<<i<<" count:"<<count<<" p:"<<p<<" sum:"<<sum<<endl;
    }
    return sum;
}

int main()
{
	int n; cin>>n;
	char arr[n];
	for(int i=0;i<n;i++)
		cin>>arr[i];
	cout<<swapCount(arr,n)<<endl;
	return 0;
}


/*
// NOTE : Doesn't give min swap
int countSwaps(char arr[],int n)
{
	stack<char> s;
	int swap = 0;

	for(int i=0;i<n;i++)
	{
		if 		(s.empty())
			s.push(arr[i]);
		else if (!s.empty())
		{
			if     (arr[i]==']')
			{
				if      (s.top()=='[')
					s.pop();
				else if (s.top()==']')
					s.push(arr[i]);
			}
			else if (arr[i]=='[')
			{
				if 		(s.top()=='[')
					s.push(arr[i]);
				else if (s.top()==']')
				{
					swap++;
					s.pop();
				}
			}
		}
	}
	return swap;
}
*/