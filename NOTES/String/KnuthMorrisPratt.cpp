#include <bits/stdc++.h>
using namespace std;

/*
KMP Algorithm is based on the idea of building DFA for string searching.

DFA is an abstract string-searching machine
- Finite number of states (including start and halt) 
- Exactly one transition for each char in alphabet.
- Accept if sequence of transition leads to halt state.

text = AABACAABABACAA
pattern = ABABAC

if in state j reading char c :
	if j == 6 halt and accept
	else move to state dfa[c][j]

                   A   B   A   B   A   C
pat.charAt(j) j  0   1   2   3   4   5   6

              A  1   1   3   1   5   1   -
  dfa[][j]           
              B  0   2   0   4   0   4   -  

              C  0   0   0   0   0   6   -

Key Difference between KMP and BruteForce :
- Need to precompute dfa[][] from pattern
- Text pointer i never decrements.

Running Time: Simulate DFA on text -> at most N character accesses.

Building DFA :-
- Include one state for each character in pattern (plus accept state).
- Matching Transition: If in state j and next char c == pat.charAt(j), go to j+1.
- Mismatch Transition: back up if in state j and next char c != pat.charAt(j). Then the last
                       j-1 characters of input are pat[1...j-1], followed by char c.



- To compute dfa[c][j] : Simulate pat[1...j-1] {state X} on DFA and take transition c.     
- VIP step basically we are simulating dummy state X through the DFA to compute values for states
  ahead in DFA. 

- Running Time: Seems to require j steps but takes only constant time if we maintain state X. 
- Running Time: M character accesses (but space/time proportional to RM)

- For each state j and char c!= pat.charAt(j), set dfa[c][j] = dfa[c][X]; then update X
  X = dfa[pat.charAt(j)][X].

 - Conclusion:
 1) Copy dfa[][X] to dfa[][j] for each mismatch case.
 2) Set dfa[pat.charAt(j)][j] to j+1 for match case.
 3) Update X.

 Proposition: KMP substring search accesses no more than M+N characters to search for a pattern
              of length M in a text of length N.
			: KMP constructs dfa[][] in time and space proportional to RM.

Larger Alphabets: Improved version of KMP constructs nfa[] in time and space proportional to M.

*/

class KMP
{
	private:
		string pat;
		int** dfa;
		int M;
		int R;

		int charAt(char c)
		{	return int(c)-int('A'); }

		void buildDFA()
		{
			dfa[charAt(pat[0])][0] = 1;
			for (int X=0,j=1; j<M; j++)
			{
				for(int c=0; c<R; c++)
					dfa[c][j] = dfa[c][X];

				dfa[charAt(pat[j])][j] = j+1;
				X = dfa[charAt(pat[j])][X];
			}

			/*
			for (int i=0;i<R;i++)
			{
				for(int j=0;j<M;j++)
					cout << dfa[i][j] << " ";
				cout << endl;
			}
			*/
		}

	public:
		KMP(string pattern)
		{
			pat = pattern;
			M = pat.size();
			R = 26;
			dfa = new int*[R];
			
			for (int i=0;i<R;i++)
				dfa[i] = new int[M];

			for (int i=0;i<R;i++)
				for(int j=0;j<M;j++)
					dfa[i][j] = 0;

			buildDFA();
		}

		int search(string txt)
		{
			int i,j,N = txt.size();
			for (i=0,j=0; i<N && j<M; i++)
				j = dfa[charAt(txt[i])][j];
			if (j == M) return i-M;
			else        return N;
		}

};

int main()
{
	KMP kmp("AACAA");	
	cout << kmp.search("AABRAACADABRAACAADABRA") << endl;
	return 0;
	
}
