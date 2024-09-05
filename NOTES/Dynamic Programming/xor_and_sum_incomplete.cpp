#include <bits/stdc++.h>
#define llu unsigned long long int
#define MOD 1000000007
using namespace std;

string xorr(string x,string y)
{
	int len_x = x.size();
	int len_y = y.size();

	string ans = "";

	int idx=len_x-1,idy=len_y-1;

	while (idx > -1 && idy > -1)
	{
		if (x[idx--]==y[idy--])
			ans = "0"+ans;
		else
			ans = "1"+ans;
	}

	while (idx > -1)
	{
		if (x[idx--]=='0')
			ans = "0"+ans;
		else
			ans = "1"+ans;
	}

	while (idy > -1)
	{
		if (y[idy--]=='0')
			ans = "0"+ans;
		else
			ans = "1"+ans;
	}

	return ans;

}

string binary_sum(string x,string y)
{
	int len_x = x.size();
	int len_y = y.size();

	string ans = "";
	bool carry = false;

	int idx = len_x-1,idy = len_y-1;

	while (idx > -1 && idy > -1)
	{
		if (x[idx]=='0' || y[idy]=='0')
		{
			if (x[idx]=='0' && y[idy]=='0')
			{
				if (!carry)
					ans = "0"+ans;
				else
				{
					ans = "1"+ans;
					carry = false;
				}
			}
			else
			{
				if (!carry)
					ans = "1"+ans;
				else
				{
					ans = "0"+ans;
				}
			}
		}
		else
		{
			if (!carry)
			{
				ans = "0"+ans;
				carry = true;
			}
			else
				ans = "1"+ans;
			
		}

		idx--;
		idy--;
	}

	while (idx > -1)
	{
		if (x[idx--]=='0')
		{
			if (!carry)
				ans = "0"+ans;
			else
			{
				ans = "1"+ans;
				carry = false;
			}
		}
		else
		{
			if (!carry)
				ans = "1"+ans;
			else
				ans = "0"+ans;
		}
	}

	while (idy > -1)
	{
		if (y[idy--]=='0')
		{
			if (!carry)
				ans = "0"+ans;
			else
			{
				ans = "1"+ans;
				carry = false;
			}
		}
		else
		{
			if (!carry)
				ans = "1"+ans;
			else
				ans = "0"+ans;
		}
	}

	if (carry)
		ans = "1"+ans;

	return ans;
}

string shl_by_1(string x)
{
	return x+"0";
}

llu give_decimal(string x)
{
	int len_x_1 = x.size()-1;

	llu sum = 0ull;


	for(int i=len_x_1;i>-1;i--)
	{
		if (x[i]=='1')
			sum += (1ull << (len_x_1-i));
	}

	return sum;
}


int main()
{
	string a,b;
	//getline(cin,a);
	//getline(cin,b);

	a = "10";
	b = "1010";

	int n;
	cin >> n;

	string final = xorr(a,b);

	for (int i=1;i<n;i++)
	{
		b = shl_by_1(b);
		final = binary_sum(final,xorr(a,b));
		//cout << i << "done\n";
	}

	cout << final << endl;
}



