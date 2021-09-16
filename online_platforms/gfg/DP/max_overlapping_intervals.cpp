#include <bits/stdc++.h>
using namespace std;


int main()
{
    int q,n;
    cin >> q;
    
    while(q--)
    {
        cin >> n;
        int* st = new int[n];
        int* ed = new int[n];
        
        int min_st=INT_MAX,max_ed=INT_MIN;
        
        for(int i=0;i<n;i++)
        {
            cin >> st[i];
            if (st[i] < min_st)
                min_st = st[i];
            
        }
        for (int i=0;i<n;i++)
        {
            cin >> ed[i];
            if (ed[i] > max_ed)
                max_ed = ed[i];
        }
        
        int* dp = new int[max_ed+2];
        
       
        
        for(int i=0;i<n;i++)
        {
            dp[st[i]]++;
            dp[ed[i]+1]--;
        }
        
       
        int curr = 0;
        int max_g = INT_MIN;
        int idx;
        for(int i=0;i<max_ed+2;i++)
        {
            curr += dp[i];
            if (curr > max_g)
            {
                max_g = curr;
                idx = i;
            }
        }
        
        cout << max_g << " " << idx << endl;
    }
    return 0;
}