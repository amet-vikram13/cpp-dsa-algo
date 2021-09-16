#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

void exch(vector<int>& v,int i,int j)
{
	int tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}

int charAtd(string txt,int N,int x,int d)
{
	// gives the character at dth position
	// in rotated string with starting position
	// as x
	if (d < N) return int(txt[(x+d)%N]);
	return -1;
}

void three_way_quicksort(string txt,int N,vector<int>& v,int lo,int hi,int d)
{
	if (lo >= hi) return;
	int lt = lo,gt = hi;
	int curr = charAtd(txt,N,v[lt],d);
	int i = lo+1;
	while (i <= gt)
	{
		int t = charAtd(txt,N,v[i],d);
		if      (curr > t) exch(v,i++,lt++);
		else if (curr < t) exch(v,i,gt--);
		else               i++;
	}

	three_way_quicksort(txt,N,v,lo,lt-1,d);
	if (curr>=0) three_way_quicksort(txt,N,v,lt,gt,d+1);
	three_way_quicksort(txt,N,v,gt+1,hi,d);
}

string BWT(const string& text) {
  string result = "";
  int n = text.size();
  vector<int> v(n);
  for(int i=0;i<n;i++)
  	v[i] = i;

  // will sort the string rotation matrix 
  // by just storing the starting index
  // of each rotated string in vector v
  three_way_quicksort(text,n,v,0,n-1,0);
  
  for (int i=0;i<n;i++)
  {
  	// now just taking the last element
  	// of each rotated string with starting
  	// position as v[i]
  	result.push_back(text[(v[i]+n-1)%n]);
  }
  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}