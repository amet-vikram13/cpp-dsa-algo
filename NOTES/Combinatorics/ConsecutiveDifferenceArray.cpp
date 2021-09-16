#include <iostream>
#include <vector>
using namespace std;

int main()
{
    /* For a given operation a=1 b=3 k=100
    to be performed on array a = [0,0,0,0,0]
    do [100,100,100,0,0]. Perform such n operations
    and find max element in resultant array
    */

    long long int n,q,a,b,k,sum=0,max=0; cin>>n>>q;
    vector<long long int>arr (n+2,0);
    while(q--)
    {
        cin>>a>>b>>k;
        /* Instead of storing numbers directly in array a
        we will store the consecutive difference in our modified
        array m i.e m[i] = a[i]-a[i-1].
        This will be done m[a] += c and m[b+1] += -c. Such that 
        cumulative sum of modifies array will give elements of array a
        a[i] = m[1]+m[2]+m[3]+...m[i];
        */

        arr[a] += k;
        arr[b+1] += -k;
    }
    
    for(long long int i=0;i<=n;i++)
    {
        sum += arr[i];
        /* The elements of the original array a, will be
        the cumulative sum of elements of array m. */
        if(sum>max)
            max = sum;
    }
    cout<<max<<endl;
    
}