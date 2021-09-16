#include <iostream>
#include <stack>
using namespace std;

int main()
{
	int n,input,curr,area,max=-1; cin>>n;
	stack<int> left;
	stack<int> right;
	

	for(int i=0;i<n;i++)
	{
		cin>>input;
		left.push(input);
	}

	
	
	int count,temp;
	
	for(int i=0;i<n;i++)
	{
	
		count = 0;
		curr = left.top();
		area = curr;

		if(!right.empty())
		{
			while(right.top() >= curr)
			{	
				temp = right.top(); right.pop();
				if(right.empty())
				{	
					
					count++;
					left.push(temp);
					break;
				}
				else
				{
					
					count++;
					left.push(temp);
				}
			}	
		}
	
		
		while(left.top()!=curr)
		{	
			temp = left.top(); left.pop();
			if(left.empty())
			{
				right.push(temp);
				break;
				
			}
			else
			{
				right.push(temp);

			}
		}
		

		
		right.push(left.top()); left.pop();

   		if(left.empty())
		{	
			area *= (count+1);
			if(area > max)
				max = area;
			break;
		}
		
	
		while(left.top() >= curr)
		{	
			temp = left.top(); left.pop();
			if(left.empty())
			{
				 
				count++;
				right.push(temp); 
				break;
			}
			else
			{
				
				count++;
				right.push(temp);
			}
		}
	
		while(right.top()!=curr)
		{	
			temp = right.top(); right.pop();
			if(right.empty())
			{
				left.push(temp);
				break;
			}
			else
			{
				left.push(temp);
			}
		}
	
		area *= (count+1);
		if(area > max)
			max = area;

	}
	
	cout<<max<<endl;
}