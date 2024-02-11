// Reverse words in a given string

#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main()
{
	int t; cin >> t;
	stack<string> st;
	string inp,tmp;
	while(t--)
	{
		cin >> inp;
		tmp = "";
		for(int i=0;i<inp.size();i++)
		{
			if (inp[i]=='.')
			{
				st.push(tmp);
				tmp = "";
				continue;
			}
			tmp.push_back(inp[i]);
		}
		st.push(tmp);
		while(st.size()>1)
		{
			cout << st.top() << ".";
			st.pop();
		}
		cout << st.top() << endl;
		st.pop();
	}
	return 0;

}