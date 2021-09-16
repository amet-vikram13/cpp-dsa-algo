#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::reverse;

int charToint(char c)
{
	switch(c)
	{
		case '$':
			return 0;
		case 'A':
			return 1;
		case 'C':
			return 2;
		case 'G':
			return 3;
		case 'T':
			return 4;
		default:
			break;
	}
	return -1;
}

char intTochar(int i)
{
	switch(i)
	{
		case 0:
			return '$';
		case 1:
			return 'A';
		case 2:
			return 'C';
		case 3:
			return 'G';
		case 4:
			return 'T';
		default:
			break;
	}
	return '!';
}

string InverseBWT(const string& bwt) {
  // write your code here
  string text = "";
  
  int* last  = new int[bwt.size()]; // last column
  int* first = new int[bwt.size()]; // first column
  int* hm = new int[bwt.size()];

  for(int i=0;i<bwt.size();i++)
  	last[i] = charToint(bwt[i]);

  // Counting Sort
  int* count = new int[6];

  for(int i=0;i<6;i++)
  	count[i] = 0;
  

  for(int i=0;i<bwt.size();i++)
  	count[last[i]+1]++;
  	

  for(int i=0;i<6;i++)
  	count[i+1] += count[i];
  

  for(int i=0;i<bwt.size();i++)
  {
  	hm[i] = count[last[i]];
  	first[count[last[i]]++] = last[i];
  }
  // 
 
  // first-last property
  int t = bwt.size();
  int k = 0;
  while(t--)
  {
  	text.push_back(intTochar(last[k]));
  	k = hm[k];
  }
  text.pop_back();
  reverse(text.begin(),text.end());
  text.push_back('$');
  
  return text;

}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
