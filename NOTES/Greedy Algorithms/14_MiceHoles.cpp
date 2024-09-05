#include <bits/stdc++.h>
#include <sstream>
#include <string>
using namespace std;

/*
We can put every mouse to its nearest hole to minimize the time. This can be done by 
sorting the positions of mice and holes. This allows us to put the ith mice to the 
corresponding hole in the holes list. We can then find the maximum difference between 
the mice and corresponding hole position.

sort mice positions (in any order)
sort hole positions 

Loop i = 1 to N:
    update ans according to the value 
    of |mice(i) - hole(i)|. It should
    be maximum of all differences.

Proof of correctness:
Let i1 < i2 be the positions of two mice and let j1 < j2 be the positions of two holes. It 
suffices to show via case analysis that

max(|i1-j1|, |i2-j2|) <= max(|i1-j2|, |i2-j1|), 
   where '|a - b|' represent absolute value of (a - b)
Since it follows by induction that every assignment can be transformed by a series of swaps 
into the sorted assignment, where none of these swaps increases the span.
*/

int main()
{

	vector<int> mice;
	vector<int> holes;
	string inp;
	int temp;
	
	getline(cin,inp);
	istringstream a(inp);
	while(a>>temp)
		mice.push_back(temp);

	getline(cin,inp);
	istringstream b(inp);
	while(b>>temp)
		holes.push_back(temp);


	sort(mice.begin(),mice.end());
	sort(holes.begin(),holes.end());

	int max = -1;
	for(int i=0;i<mice.size();i++)
	{
		if(abs(mice[i]-holes[i]) > max)
			max = abs(mice[i]-holes[i]);
	}
	cout<<max<<endl;	
	
	return 0;
}