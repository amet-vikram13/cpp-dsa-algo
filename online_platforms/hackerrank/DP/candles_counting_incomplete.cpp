#include <bits/stdc++.h>
using namespace std;

struct Candle
{
	int height;
	int color;
};

int main()
{
	int n,k;

	cin >> n >> k;

	Candle* arr = new Candle[n];

	for(int i=0;i<n;i++)
		cin >> arr[i].height >> arr[i].color;

	
}