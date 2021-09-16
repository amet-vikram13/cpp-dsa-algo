#include <iostream>
#include <queue>
#include <functional>
#include <vector>
using namespace std;

int main()
{
	int N,K,input,res=0,flag=1; cin>>N>>K;
	priority_queue<int,vector<int>,greater<int> > pq;
	for(int i=0;i<N;i++)
	{
		cin>>input;
		pq.push(input);
	}

	while(pq.top() < K)
	{
		if(pq.size()==1)
		{
			flag = 0;
			cout<<-1<<endl;
			break;
		}

		int first  = pq.top(); pq.pop();
		int second = pq.top(); pq.pop();
		pq.push(first+2*second);
		res++;
	}

	if(flag)
		cout<<res<<endl;


	return 0;
}