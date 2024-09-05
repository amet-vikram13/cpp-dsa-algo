#include <bits/stdc++.h>
#define MOD 1000000007
#define llu unsigned long long int
using namespace std;

// Not a DP question
// TAKEAWAY :- Understand digit frquency in a number substring
//             It can be expressed as 1,10,100,1000 or simply combining
//			   all frequencies 1111. USE MOD everywhere
//             In DP strings, arrays basically memoization starts from tail i.e end
llu substr_sum(string inp)
{
    llu sum = 0llu;
    llu freq = 1llu;
    len=inp.size(), num;

    for(int i=len-1;i>-1;i--)
    {
    	num = int(inp[i]-'0');

    	sum = (sum%MOD + (num*freq*(i+1))%MOD)%MOD;

    	freq = (freq*10 + 1)%MOD;
    }



    /* Almost CRACKED : instead of counting digit frquency
                        in a loop with the help hd pointer
                        for i = 0 to hd i.e for 1,10,100...
                        use 111111.....
    int hd=0;
    for (int i=len-1;i>-1;i--)
    {
        num = int(inp[i]-'0');

        if (num == 0)
        {
            hd++;
            continue;
        }

        for(int i=0;i<=hd;i++)
        {
            llu tmp = (llu)pow(10,i);

            sum = (sum%MOD + ((len-hd)*tmp*num)%MOD)%MOD;
        }

        hd++;
    }
    */

    return sum;
}

int main()
{
    string inp;
    getline(cin,inp);

    cout << substr_sum(inp) << endl;

    return 0;


}
