#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

int charToint(char c)
{
	if (c == '$') return 0;
	if (c == 'A') return 1;
	if (c == 'C') return 2;
	if (c == 'G') return 3;
	return 4;
}

int* sortCharacters(const string S)
{
	int* order = new int[S.size()];
	int* count = new int[5];
	for(int j=0;j<5;j++)
		count[j] = 0;
	for(int i=0;i<S.size();i++)
		count[charToint(S[i])] = count[charToint(S[i])]+1;
	for(int j=1;j<5;j++)
		count[j] = count[j] + count[j-1];
	for(int i=S.size()-1;i>-1;i--)
	{
		count[charToint(S[i])] = count[charToint(S[i])]-1;
		order[count[charToint(S[i])]] = i;
	}
	return order;
}

int* computeCharClasses(const string S,int* order)
{
	int* class_arr = new int[S.size()];
	class_arr[order[0]] = 0;
	for(int i=1;i<S.size();i++)
	{
		if(S[order[i]]!=S[order[i-1]])
			class_arr[order[i]] = class_arr[order[i-1]]+1;
		else
			class_arr[order[i]] = class_arr[order[i-1]];
	}
	return class_arr;
}

int* sortDoubled(const string S,int L,int* order,int* class_arr)
{
	int* new_order = new int[S.size()];
	int* count = new int[S.size()];
	for(int j=0;j<S.size();j++)
		count[j] = 0;
	for(int i=0;i<S.size();i++)
		count[class_arr[i]] = count[class_arr[i]]+1;
	for(int j=1;j<S.size();j++)
		count[j] = count[j]+count[j-1];
	int start,cl;
	for(int i=S.size()-1;i>-1;i--)
	{
		start = (order[i]-L+S.size())%(S.size());
		cl = class_arr[start];
		count[cl] = count[cl]-1;
		new_order[count[cl]] = start;
	}
	return new_order;
}


int* updateClasses(const string S,int* new_order,int* old_class,int L)
{
	int* new_class = new int[S.size()];
	new_class[new_order[0]] = 0;
	int curr,prev,mid,mid_prev;
	for(int i=1;i<S.size();i++)
	{
		curr = new_order[i]; prev = new_order[i-1];
		mid = (curr+L); mid_prev = (prev+L)%(S.size());
		if ((old_class[curr]!=old_class[prev])||(old_class[mid]!=old_class[mid_prev]))
			new_class[curr] = new_class[prev]+1;
		else
			new_class[curr] = new_class[prev];
	}
	return new_class;
}

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text start.
int* BuildSuffixArray(const string S) {
  // Implement this function yourself
  int* order = sortCharacters(S);
  int* class_arr = computeCharClasses(S,order);
  int L = 1;
  while(L<S.size())
  {
  	order = sortDoubled(S,L,order,class_arr);
  	class_arr = updateClasses(S,order,class_arr,L);
  	L = 2*L;
  }
  return order;
}

int main() {
  string text;
  cin >> text;
  int* suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < text.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
