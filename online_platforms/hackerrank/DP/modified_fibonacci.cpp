#include <bits/stdc++.h>
using namespace std;

// TAKEAWAY :- Simple DP

string addition(string num1,string num2)
{
	int len1 = num1.size();
	int len2 = num2.size();
	if (len1==0 || len2==0)
		return "0";


	vector<int> result(((len1 > len2)?len1+1:len2+1),0);

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

string multiply(string inp1, string inp2)
{
	int len1 = inp1.size();
	int len2 = inp2.size();

	if (len1==0 || len2==0)
		return "0";

	vector<int> result(len1+len2,0);

	int i_n1=0,i_n2,num1,num2,carry,sum;

	for (int i=len1-1;i>-1;i--)
	{
		i_n2 = 0;
		num1 = int(inp1[i]-'0');
		carry = 0;
		sum = 0;

		for (int j=len2-1;j>-1;j--)
		{
			num2 = int(inp2[j]-'0');
			sum  = num1*num2 + result[i_n1+i_n2] + carry;
			result[i_n1+i_n2] = sum%10;
			carry = sum / 10;
			i_n2++;
		}

		if (carry > 0)
			result[i_n1+i_n2] += carry;

		i_n1++;
	}

	int i = result.size()-1;
	while (i>=0 && result[i]==0)
		i--;

	if (i==-1)
		return "0";

	string ans = "";
	while (i >= 0)
		ans += to_string(result[i--]);

	return ans;
}

string modified_fibo(int t1,int t2,int n)
{
	string* ans = new string[n];

	ans[0] = to_string(t1);
	ans[1] = to_string(t2);

	for (int i=2;i<n;i++)
	{
		ans[i] = addition(ans[i-2],multiply(ans[i-1],ans[i-1]));
	}

	return ans[n-1];
}



int main()
{
	int t1,t2,n;

	cin >> t1 >> t2 >> n;

	cout<<modified_fibo(t1,t2,n)<<endl;

}