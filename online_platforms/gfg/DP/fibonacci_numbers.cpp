#include <bits/stdc++.h>
#define llu long long int
#define mod 1000000007
using namespace std;

llu* f = new llu[1001];

void fib()
{
    f[0] = 1ll;
    f[1] = 1ll;
    for(int i=2;i<=1000;i++)
    {
        f[i] = (f[i-1]%mod + f[i-2]%mod)%mod;
    }
    
}

int main()
{
    fib();
    int t,q; cin>>t;
    while(t--)
    {
        cin>>q;
        cout<<f[q-1]<<endl;
        
    }
    return 0;
}