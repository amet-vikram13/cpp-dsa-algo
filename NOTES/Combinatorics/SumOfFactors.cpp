// Algorithm related to Sieve of Erothenesis


#include <iostream>
using namespace std;


/* Better program to get sum of 
   factors. 
*/
int main()
{
	int t; cin>>t;
	long long sumf[1000001],x,i,j;
	const long long MM = 1000000;
	
	for(i=1;i<=MM;i++)
	{
		for(j=i;j<=MM;j+=i)
			sumf[j]+=i;
	}
	
	while(t--)
	{
		cin>>x;
		cout<<sumf[x]<<endl;
	}

	return 0;
}

/*
int main()
{
	int t; cin>>t;
	long long n,ans,i;
	while(t--)
	{
		cin>>n;
		ans=0;

		for(i=1;i*i<=n;i++)
		{
			if(n%i==0)
				ans+=i+n/i;

			if(i*i==n)
				ans-=i;
		}
		cout<<ans<<endl;

	}
	return 0;

}
*/
