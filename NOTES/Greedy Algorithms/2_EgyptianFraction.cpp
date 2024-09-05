#include <bits/stdc++.h>
using namespace std;

/*
We can generate Egyptian Fractions using Greedy Algorithm. For a given number of the form 
‘nr/dr’ where dr > nr, first find the greatest possible unit fraction, then recur for the 
remaining part. 
For example, consider 6/14, we first find ceiling of 14/6, i.e., 3. So the 
first unit fraction becomes 1/3, then recur for (6/14 – 1/3) i.e., 4/42.

########
The Greedy algorithm works because a fraction is always reduced to a form where denominator 
is greater than numerator and numerator doesn’t divide denominator. For such reduced forms, 
the highlighted recursive call is made for reduced numerator. So the recursive calls keep on 
reducing the numerator till it reaches 1.
########
*/

void printEgyptian(int nr,int dr)
{
	// If either numerator or denominator is 0
	if(nr == 0 || dr == 0)
		return;

	// If numerator divides denominator, then simple division
    // makes the fraction in 1/n form
	if(dr%nr == 0)
	{
		cout<<"1/"<<dr/nr;
		return;
	}

	// If denominator divides numerator, then the given number
    // is not fraction
	if(nr%dr == 0)
	{
		cout<<nr/dr;
		return;
	}

	// If numerator is more than denominator
	if(nr > dr)
	{
		cout<<nr/dr<<" + ";
		printEgyptian(nr%dr,dr);
		return;
	}

	// We reach here dr > nr and dr%nr is non-zero
    // Find ceiling of dr/nr and print it as first
    // fraction
	int n = dr/nr + 1;
	cout<<"1/"<<n<<" + ";
	
	// Recur for remaining part
	printEgyptian(nr*n-dr,dr*n);
}

int main()
{
	int nr = 12,dr = 13;
	printEgyptian(nr,dr);
	cout<<endl;
	return 0;
}