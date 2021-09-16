#include <bits/stdc++.h>
using namespace std;

int coin_game(int* arr,int n)
{
    int** dp = new int*[n];
    for(int i=0;i<n;i++)
        dp[i] = new int[n];
        
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            dp[i][j] = 0;
    
    for(int i=0;i<n;i++)
        dp[i][i] = arr[i];

    
}

int main()
{
    int t,n;
    cin >> t;
    while(t--)
    {
        cin >> n;
        
        int* arr = new int[n];
        
        for(int i=0;i<n;i++)
            cin >> arr[i];
        
        
    }
}
