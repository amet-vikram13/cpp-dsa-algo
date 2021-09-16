#include <bits/stdc++.h>
using namespace std;


int buy_lands(int** p,int n)
{
	// p[i][0] -- width
	// p[i][1] -- length

	int* c = new int[n];

	// Thre are 2 types of lands Group Lands,
	// Dissolved Lands.
	// Dissolved Lands are inside Group Lands.
	list<pair<int,int> > group;
	
	int curr,mcurr,twid,tlen,cwid,clen,mwid,mlen,fwid,flen,itr,mitr;
	bool flag;

	// Minimal cost of acquiring lands after
	// seeing i lands is c[i];
	c[0] = p[0][0]*p[0][1];
	group.push_back(make_pair(p[0][0],p[0][1]));

	for(int i=1;i<n;i++)
	{
		cwid = p[i][0];
		clen = p[i][1];
		curr = c[i-1];
		mcurr = curr + (cwid*clen);
		fwid  = cwid;
		flen  = clen;
		mitr = 0;
		itr = -1;
		flag = false;
		
		for(auto it=group.begin();it!=group.end();it++)
		{
			itr++;
			twid = it->first;
			tlen = it->second;

			mwid = ((cwid >= twid) ? cwid:twid);
			mlen = ((clen >= tlen) ? clen:tlen);

			if ( (curr - (twid*tlen) + (mwid*mlen)) <= mcurr )
			{
				mcurr = curr - (twid*tlen) + (mwid*mlen);
				fwid = mwid;
				flen = mlen;
				mitr = itr;
				flag = true;
			}
		}

		if (flag)
		{
			auto it = group.begin();
			auto nx = next(it,mitr);
			nx->first = fwid;
			nx->second = flen;
		}
		else
			group.push_back(make_pair(fwid,flen));

		c[i] = mcurr;
	}
	
	return c[n-1];

}

int main()
{
	int n;
	cin>>n;

	int** p = new int*[n];
	for(int i=0;i<n;i++)
		p[i] = new int[2];

	int i = 0;
	while(n--)
	{
		cin>>p[i][0]>>p[i][1];
		i++;
	}
    cout<<endl<<buy_lands(p,i)<<endl;
	return 0;
}