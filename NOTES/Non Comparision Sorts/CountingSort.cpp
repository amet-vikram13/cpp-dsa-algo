#include <bits/stdc++.h>
using namespace std;


void counting_sort(int* arr,int n)
{
	int* count = new int[11];
	int* aux = new int[n];

	for(int i=0;i<11;i++)
		count[i] = 0;

	for(int i=0;i<n;i++)
		count[arr[i]+1]++;

	for(int i=0;i<10;i++)
		count[i+1] += count[i];

	for(int i=0;i<n;i++)
		aux[count[arr[i]]++] = arr[i];

	for (int i=0;i<n;i++)
		cout << aux[i] << " ";

	cout << endl;

	return;
}

int main()
{
	int arr[] = {1,4,1,2,7,5,2};
	counting_sort(arr,7);
}