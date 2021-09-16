#include <iostream>
#include <stack>
using namespace std;

int main()
{
	stack<int> s1,temp; stack<int> s2; stack<int> s3;
	int n=0,input,sum=0; int arr[3];

	while(n!=3)
	{
		cin>>arr[n];
		n++;
	}

	/* Instead of storing the height directly
	into stack store the cumulative sum of
	heights. */
	for(int j=0;j<arr[0];j++)
	{
		cin>>input;
		temp.push(input);
	}
	while(!temp.empty())
	{
		sum += temp.top();
		s1.push(sum);
		temp.pop();
	}

	sum = 0;

	for(int j=0;j<arr[1];j++)
	{
		cin>>input;
		temp.push(input);
	}
	while(!temp.empty())
	{
		sum += temp.top();
		s2.push(sum);
		temp.pop();
	}

	sum = 0;

	for(int j=0;j<arr[2];j++)
	{
		cin>>input;
		temp.push(input);
	}
	while(!temp.empty())
	{
		sum += temp.top();
		s3.push(sum);
		temp.pop();
	}

	int top1,top2,top3,maxele,flag=1;

	while(true)
	{
		if(!s1.empty())
			top1 = s1.top();
		else
		{	
			flag = 0;
			break;
		} 
		
		if(!s2.empty())
			top2 = s2.top();
		else
		{	
			flag = 0;
			break;
		} 
		
		if(!s3.empty())
			top3 = s3.top();
		else
		{	
			flag = 0;
			break;
		} 
		
		if(top1==top2)
			if(top2==top3)
				break;

		/* Pop only that element from stacks whose total height is
		maximum because we have to ensure that heights get equal
		for all three stacks. */

	maxele = ((top1 > top2) ? top1 : top2);
		maxele = ((top3 > maxele) ? top3 : maxele);

		if(top1==maxele)
			s1.pop();

		if(top2==maxele)
			s2.pop();

		if(top3==maxele)
			s3.pop();
	}

	

	if(flag==0)
		cout<<flag<<endl;
	else
		cout<<top1<<endl;
	
	return 0;


}