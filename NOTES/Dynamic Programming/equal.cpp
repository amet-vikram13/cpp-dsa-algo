#include <bits/stdc++.h>
using namespace std;

// TAKEAWAY :- NOT A DP QUESTION
//             Here we just count min number of operations to bring
//             a value down to min value, or min_value-1,min_value-2..
//             and so on, the min number of operations is always in fixed
//             order i.e 5, 2, 1 and since 1 is there so every value can be changed to 
//             any value

int min_op(int* arr,int i,int minn)
{
    // Fixed number of steps
    int value = arr[i]-minn;
    return ((value/5) + ((value%5)/2) + (((value%5)%2)/1));
}

int make_equal_op(int* arr,int n)
{
    int minn = INT_MAX;
    int count = 0;
    for(int i=0;i<n;i++)
    {
        if (arr[i]<minn)
            minn = arr[i];

        if (i!=0)
            if (arr[i]==arr[i-1])
                count++;
    }

    if (count==n-1)
        return 0;

    // Possible that min number of operations comes for some
    // other base, base could be negative also.
    int base[6] = {minn,minn-1,minn-2,minn-3,minn-4,minn-5};
    int* summ = new int[6];
    int sum_min = INT_MAX;

    for(int i=0;i<6;i++)
    {
            for(int j=0;j<n;j++)
            {
                if (base[i]!=arr[j])
                    summ[i] += min_op(arr,j,base[i]);
            }
    }

    for(int i=0;i<6;i++)
        if (sum_min>summ[i])
            sum_min = summ[i];

    return sum_min;
}

int main()
{
    int t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        int* arr = new int[n];
        for(int i=0;i<n;i++)
            cin>>arr[i];
        cout<<make_equal_op(arr,n)<<endl;
    }
    return 0;
}