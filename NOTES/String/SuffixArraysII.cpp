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
using std::stable_sort;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
string text;

bool policy(int i,int j)
{
  return text.substr(i).compare(text.substr(j)) < 0;
}

vector<int> BuildSuffixArray() {
  int N = text.size();
  vector<int> v(N);
  for(int i=0;i<N;i++)
    v[i] = N-1-i;
  stable_sort(v.begin(),v.end(),policy);
  return v;
}

int main() {
  std::ios_base::sync_with_stdio(false); 
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray();
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  return 0;
}
