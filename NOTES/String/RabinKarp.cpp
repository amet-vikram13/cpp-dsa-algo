#include <bits/stdc++.h>
#define llu unsigned long long int
using namespace std;

/*

Basic Idea = Modular Hashing
- Compute a hash of pattern characters 0 to M-1
- for each i, compute a hash text characters i to M+i-1
- if pattern hash = text substring hash, check a match.

Modular Hash Function: Using the notation ti for charAt(txt[i]),

xi = ti*R^M-1 + ti+1*R^M-2 + ... + ti+M-1R^0 (mod Q).

Intution: M-digit, base-R integer(Radix), modulo Q.

Horner's method: Linear-time method to evaluate degree-M polynomial.
Key property: can update hash function in constant time!

xi+1 = (xi - ti*R^M-1) * R + ti+M
*/


class RabinKarp
{
	private:
		string pat;
		llu patHash;    // pattern hash value
		int M;    		// pattern length
		llu Q;    		// modulus
		int R;    		// Radix
		llu RM;   		// R^(M-1)%Q

		int charAt(char c)
		{	return int(c)-int('0'); }

		llu hash(string key)
		{
			llu h = 0;
			for(int j=0;j<M;j++)
				h = (h*R + charAt(key[j])) % Q;
			return h;
		}

	public:
		RabinKarp(string pattern)
		{
			pat = pattern;
			M = pat.size();
			R = 10;
			Q = 997ull;

			RM = 1ull;
			for (int i=1;i<=M-1;i++)
				RM = (R* RM) % Q;
			patHash = hash(pat); 
		}

		int search(string txt)
		{
			
		}
};