#include <bits/stdc++.h>
using namespace std;

int* fact = new int[10];
int* call = new int; 



int factorial(int* fact,int n)
{
    cout<<"Called "<<++(*call)<<" time\n";
    if (fact[n]!=-1) { return fact[n]; }
    else if (n <= 1) { return 1; }
    else 
    { 
        fact[n] = n * factorial(fact,n-1);
        return fact[n]; 
    }
    
}


int main()
{
    for (int i=0;i<10;i++)
        fact[i] = -1;

    int q,n;
    cin >> q;


    
    while(q--)
    {
        cin >> n;
        *call = 0;
        cout << factorial(fact,n) << endl;
    }
    
    return 0;
}