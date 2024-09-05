#include <bits/stdc++.h>
#define llu unsigned long long int
using namespace std;

// GFG - no_of_ways_coin_change.cpp

llu another_bottomup_coin_change(int n,int* c,int m)
{
    llu* ways = new llu[n+1];
    ways[0] = 1;

    for(int j=0;j<m;j++)
        for(int i=c[j];i<=n;i++)
            ways[i] += ways[i-c[j]];

    return ways[n];
}

int main()
{
    int n,m;
    cin>>n>>m;
    int* c = new int[m];
    for(int i=0;i<m;i++)
        cin>>c[i];
    cout<<another_bottomup_coin_change(n,c,m)<<endl;
    return 0;
}
