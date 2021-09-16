#include <iostream>
using namespace std;

// TAKEAWAY :- VIP LEARNING DP QUES

int min_coin_change(int v,int* c,int n)
{
    int* min_change = new int[v+1];
    min_change[0] = -1;
    
    for(int i=1;i<=v;i++)
    {
        min_change[i] = INT_MAX;
        for(int j=0;j<n;j++)
        {
            if(i==c[j])
            {
                min_change[i] = 1;
                break;
            }
            
            if(i-c[j]>0)
                if (min_change[i-c[j]]!=-1)
                    if(min_change[i] > 1+min_change[i-c[j]])
                        min_change[i] = 1+min_change[i-c[j]];

        

        }

        if (min_change[i]==INT_MAX)
            min_change[i] = -1;

        
    }

    return min_change[v];
}

int main()
{
    int t,v,n;
    cin>>t;
    while(t--)
    {
        cin>>v>>n;
        int* c = new int[n];
        for(int i=0;i<n;i++)
            cin>>c[i];
        cout<<min_coin_change(v,c,n)<<endl;
     
    }
    return 0;
}