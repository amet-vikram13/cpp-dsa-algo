#include <bits/stdc++.h>
#define llu unsigned long long int
using namespace std;


// TAKEAWAY :- VIP LEARNING DP QUES
//

// Bottom up tiling problem
llu tiling(int n)
{
    llu** ways = new llu*[n+1];
    for(int i=0;i<=n;i++)
        ways[i] = new llu[2];
    
    // ways[i][0] - number of ways to tile i length with last tile 2X1
    // ways[i][1] - number of ways to tile i length with last tile 1X2
    //  __ __ __ __ __ __ __ __
    // |                          1X2 } 2X1 2X1
    // |__ __ __ __ __ __ __ __   1X2 }

    ways[0][0] = 0ll;
    ways[0][1] = 0ll;
    ways[1][0] = 1ll;
    ways[1][1] = 0ll;
    ways[2][0] = 1ll;
    ways[2][1] = 1ll;
    
    for(int i=3;i<=n;i++)
    {
        ways[i][0] = ways[i-1][0] + ways[i-1][1];
        ways[i][1] = ways[i-2][0] + ways[i-2][1];
    }
    
    return (ways[n][0]+ways[n][1]);
}

int main()
{
    int t,n;
    cin>>t;
    
    while(t--)
    {
        cin>>n;
        
        cout<<tiling(n)<<endl;
    }
    
    return 0;
}