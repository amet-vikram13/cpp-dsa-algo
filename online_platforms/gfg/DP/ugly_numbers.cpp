#include <bits/stdc++.h>
#define llu long long int
using namespace std;

long long int* ugly_numbers()
{
    llu * u = new llu[10001];
    llu next_mul_2;
    llu next_mul_3;
    llu next_mul_5;
    int next_idx_2 = 0;
    int next_idx_3 = 0;
    int next_idx_5 = 0;
    u[0] = 1ll;
    int i=1;
    llu min;

    while(i < 10001)
    {
        next_mul_2 = 2ll*u[next_idx_2];
        next_mul_3 = 3ll*u[next_idx_3];
        next_mul_5 = 5ll*u[next_idx_5];

        min = ((next_mul_2 < next_mul_3) ? next_mul_2 : next_mul_3);
        min = ((min < next_mul_5) ? min : next_mul_5);

        if (min==next_mul_2)
            next_idx_2++;
        if (min==next_mul_3)
            next_idx_3++;
        if (min==next_mul_5)
            next_idx_5++;

        u[i] = min;
        i++;
    }

    return u;
}

int main()
{
    llu* ans = ugly_numbers();
    int t,q; cin>>t;
    while(t--)
    {
        cin>>q;
        cout<<ans[q-1]<<endl;
    }
    return 0;
}