#include <bits/stdc++.h>
using namespace std;

int longestConsecutiveSubsequence(int arr[],int n)
{
	unordered_set<int> s; 
    int ans = 0; 
  
     
    for (int i = 0; i < n; i++) 
        s.insert(arr[i]); 
  
     
    for (int i=0; i<n; i++) 
    { 
       
        if (s.find(arr[i]-1) == s.end()) 
        { 
            
            int j = arr[i]; 
            while (s.find(j) != s.end()) 
                j++; 

            ans = max(ans, j - arr[i]); 
        } 
    } 
    return ans; 	
}

int main()
{
	int arr[] = {1,9,3,10,4,20,2};
	int n = 7;
	cout << longestConsecutiveSubsequence(arr,n) << endl;	
}
