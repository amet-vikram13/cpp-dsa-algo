#include <bits/stdc++.h>
using namespace std;

int* counting_sort_largest_even(string n)
{
	int* count = new int[11];
	int* aux = new int[n.size()];

	for(int i=0;i<11;i++)
		count[i] = 0;

	for(int i=0;i<n.size();i++)
		count[int(n[i]-'0')+1]++;

	for(int i=0;i<10;i++)
		count[i+1] += count[i];

	for(int i=0;i<n.size();i++)
		aux[count[int(n[i]-'0')]++] = int(n[i]-'0');

	if (aux[0]%2==0)
		return aux;

	int idx = -1;
	for(int i=1;i<n.size();i++)
	{
		if (aux[i]%2==0)
		{
			idx = i;
			break;
		}
	}

	if (idx == -1)
		return aux;

	int* new_aux = new int[n.size()];

	for(int i=0;i<idx;i++)
		new_aux[i+1] = aux[i];
	for(int i=idx+1;i<n.size();i++)
		new_aux[i] = aux[i];

	new_aux[0] = aux[idx];

	return new_aux;
}


int main()
{
	int t;
	string n;

	cin >> t;
	cin.get();

	while(t--)
	{
		getline(cin,n);

		int* ans = counting_sort_largest_even(n);

		for(int i=n.size()-1;i>-1;i--)
			cout<<ans[i];
		cout << endl;


	}
}