#include <bits/stdc++.h>
using namespace std;

int decoding(string s)
{
	int n = s.size();
	int* c = new int[n];
	int num;
	
	c[0] = 1;
	
	num = (s[0] - '0')*10 + (s[1] - '0');

	if (s[1]-'0'==0)
	{
		c[0] = 0;
		c[1] = 1;
	}
	else
	{
		if (num <= 26)
			c[1] = 2;
		else
			c[1] = 1;
	}
		
	

	for(int i=2;i<n;i++)
	{
		//cout<<c[i-1]<<endl;
		c[i] = c[i-1];
		//cout<<i<<" "<<c[i]<<endl;

		
		num = (s[i-1] - '0')*10 + (s[i] - '0');

		if (s[i]-'0'==0)
		{
			c[i] = 0;
		}
		else if (s[i-1]-'0'==0)
		{
			continue;
		}
		
		if (num <= 26)
		{
			//cout<<"here "<<num<<endl;
			c[i] += c[i-2];
			//cout<<"here "<<c[i]<<endl;
		}
		

		//cout<<c[i]<<endl<<endl;;
	}

	return c[n-1];

}

int main()
{
	string inp;

	while(1)
	{
		getline(cin,inp);

		if (inp.size()==1)
			if(inp[0]-'0'==0)
				break;

		cout<<decoding(inp)<<endl;
	}

	return 0;
}