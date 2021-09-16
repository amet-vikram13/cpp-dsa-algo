#include <bits/stdc++.h>
using namespace std;

int mining(int** mat,int n,int m)
{
    int** c = new int*[n];
    for(int i=0;i<n;i++)
        c[i] = new int[m];
    
    // c[i][j] -- max gold Value till j columns reaching [i][j] cell
    
    for(int i=0;i<n;i++)
        c[i][0] = mat[i][0];

    int st,ed,max;

    for(int j=1;j<m;j++)
    {
        for(int i=0;i<n;i++)
        {
            st = i-1;
            if (st == -1)
                st++;

            ed = i+1;
            if (ed == n)
                ed--;

            max = -1;
            for(int k=st;k<=ed;k++)
                if (c[k][j-1] + mat[i][j] > max)
                    max = c[k][j-1] + mat[i][j];

            c[i][j] = max;
        }
    }

    max = -1;
    for(int i=0;i<n;i++)
        if (c[i][m-1] > max)
            max = c[i][m-1];

    return max;
}

int main()
{
    int t,n,m;
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        int** mat = new int*[n];
        for(int i=0;i<n;i++)
            mat[i] = new int[m];
            
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                cin>>mat[i][j];
        
        cout<<mining(mat,n,m)<<endl;
    }
    
    return 0;
}