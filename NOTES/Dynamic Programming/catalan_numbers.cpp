#include <bits/stdc++.h>
#define llu unsigned long long int
using namespace std;

string multiply(string num1,string num2)
{
	int len1 = num1.size();
	int len2 = num2.size();
	if (len1==0 || len2==0)
		return "0";

	vector<int> result(len1+len2,0);

	int i_n1 = 0;
	int i_n2 = 0;

	for(int i=len1-1;i>=0;i--)
	{
		int carry = 0;
		int n1 = num1[i]-'0';

		i_n2 = 0;

		for(int j=len2-1;j>=0;j--)
		{
			int n2 = num2[j]-'0';
			int sum = n1*n2 + result[i_n1 + i_n2] + carry;
			carry = sum/10;
			result[i_n1+i_n2] = sum%10;
			i_n2++; 
		}

		if (carry > 0)
			result[i_n1+i_n2] += carry;

		i_n1++;
	}

	int i = result.size()-1;
	while(i>=0 && result[i]==0)
		i--;

	if (i==-1)
		return "0";

	string s = "";

	while (i>=0)
		s += to_string(result[i--]);

	return s;
}

string addition(string num1,string num2)
{
	int len1 = num1.size();
	int len2 = num2.size();
	if (len1==0 || len2==0)
		return "0";

	vector<int> result(len1+len2,0);

	int i = len1-1;
	int j = len2-1;
	int n1,n2,sum,carry=0,pos=0;

	while(i>=0 && j>=0)
	{
		n1 = num1[i--]-'0';
		n2 = num2[j--]-'0';
		sum = n1+n2+carry;
		result[pos++] = sum%10;
		carry = sum/10;
	}

	while(i>=0)
	{
		n1 = num1[i--]-'0';
		sum = n1+carry; 
		result[pos++] = sum%10;
		carry = sum/10;
	}

	while(j>=0)
	{
		n2 = num2[j--]-'0';
		sum = n2+carry; 
		result[pos++] = sum%10;
		carry = sum/10;
	}
	
	if(carry > 0)
		result[pos++] = carry;

	string s = "";

	pos--;
	while(pos>=0)
		s += to_string(result[pos--]);

	return s;
}


int n = 101;
vector<string> c(n,"0");

void catalan_numbers()
{
	c[0] = "1";
	c[1] = "1";
	for(int l=2;l<n;l++)
	{
		int i = 0;
		int j = l-1;
		while(i<l)
		{
			c[l] = addition(c[l],multiply(c[i],c[j]));
			i++;
			j--;
		}
	}
}

int main()
{
    catalan_numbers();
    int t,q;
    cin >> t;
    while(t--)
    {
        cin>>q;
        cout<<c[q]<<endl;
        
    }
    return 0;
}