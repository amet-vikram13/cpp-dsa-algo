/*
Sieve of Eratosthenes

1. Create a list of consecutive integers from 2 to n: (2, 3, 4,...., n).

2. Initially, let p equal 2, the first prime number.

3. Starting from p, count up in increments of p and mark each of these numbers greater than p itself in the list. 
   These numbers will be 2p, 3p, 4p, etc.; note that some of them may have already been marked.

4. Find the first number greater than p in the list that is not marked. If there was no such number, stop. 
   Otherwise, let p now equal this number (which is the next prime), and repeat from step 3.
*/

#include <iostream>
using namespace std;

void SieveOfEratosthenes(int n)
{
	int prime[n+1] {}; // NOTE using negative logic 0~True
	int p=2;
	while(p*p<=n)
	{
		if(!prime[p])
		{
			for(int i=p+p;i<=n;i+=p)
				prime[i]=1;
		}
		p+=1;
	}

	for(p=2;p<=n;p++)
		if(!prime[p])
			cout<<p<<endl;
}

int main()
{
	int n; cin>>n;

	SieveOfEratosthenes(n);

	return 0;

}

/*
#include <iostream>
using namespace std;

bool testingprime(int k)
{
	if(k<2)
		return false;
	if(k==2 || k==3)
		return true;
	if(k%2==0 || k%3==0)
		return false;
	for(int i=5;i*i<=k;i+=6)
		if(k%i==0 || k%(i+2)==0)
			return false;
	return true;
}

int main()
{
	int n; cin>>n;
	for(int i=1;i<=n;i++)
		if(testingprime(i))
			cout<<i<<endl;
	return 0;
}
*/