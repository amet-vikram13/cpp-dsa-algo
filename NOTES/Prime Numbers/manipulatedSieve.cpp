#include <bits/stdc++.h>
#define llu unsigned long long int
using namespace std;

const llu MAX_SIZE = 1000001ull;
vector<bool> isPrime(MAX_SIZE,true);
vector<llu> prime;
vector<llu> SPF(MAX_SIZE);

void manipulatedSieve(llu N)
{
	isPrime[0] = isPrime[1] = false;
	
	for(llu i=2;i<N;i++)
	{
		if(isPrime[i])
		{
			prime.push_back(i);
			SPF[i] = i;
		}

		for(llu j=0;j<prime.size() && i*prime[j]<N && prime[j]<=SPF[i];j++)
		{
			isPrime[i*prime[j]] = false;
			SPF[i*prime[j]] = prime[j];
			
		}
	}
}

int main()
{
	int N; cin >> N;
	manipulatedSieve(N);
	for(int i=0;i<N;i++)
		if(isPrime[i])
			cout << i << " ";
	cout << endl;
	return 0;
}
