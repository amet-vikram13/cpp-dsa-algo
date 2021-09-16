#include <bits/stdc++.h>
using namespace std;

void fitShelves(int w,int m,int n)
{
	pair<pair<int,int>,int> ans;
	// n is larger shelf
	if (w%n == 0)
		cout<<"0 "<<w/n<<" "<<"0\n";
	else
	{
		int rem,emsp;            // utility variables
		int nc      = n*(w/n);   // area covered by n shelf
		int mc      = 0;         // area covered by m shelf
		int minEmsp = w - nc;    // initial empty space left on wall
		
		ans = {{0,w/n},minEmsp}; // default value
		
		// Starting with maximum number of larger
		// shelves, we just now have to check where
		// empty space is minimum after fitting smaller
		// shelves in remaining region. And then decreasing
		// number of maximum shelf one by one.
		// This will ensure that variable ans holds value
		// only with max possible larger shelf number and min 
		// empty space. No clashes will occur
		
		while (nc > -1)
		{
			rem  = w - nc;
			mc   = m*(rem/m);
			emsp = w - (mc+nc);
			//cout<<"nc:"<<nc<<" mc:"<<mc<<" emsp:"<<emsp<<endl;
			if (emsp < minEmsp)
			{
				//cout<<"inserted\n";
				minEmsp = emsp;
				ans = {{mc/m,nc/n},emsp};
			}
			if (emsp == 0)
				break;
			nc -= n;
		}
	}
	cout<<ans.first.first<<" "<<ans.first.second<<" "<<ans.second<<endl;
}


int main()
{
	int w,m,n; cin>>w>>m>>n;
	fitShelves(w,m,n);
	return 0;
}