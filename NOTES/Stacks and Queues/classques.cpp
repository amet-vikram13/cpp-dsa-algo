bool checkStackPermutation(int ip[],int op[],int n)
{
	queue<int> input,output;

	for(int i=0;i<n;i++)
	{
		input.push(ip[i]);
		output.push(op[i]);
	}

	stack<int> tempStack;
	while(!input.empty())
	{
		int ele = input.front();
		input.pop();
		if(ele==output.front())
		{
			output.pop();
			while(!tempStack.empty())
			{
				if(tempStack.top()==output.front())
				{
					tempStack.pop();
					output.pop();
				}
				else
					break;
			}
		}
		else
			tempStack.push(ele);
	}

	return (input.empty()&&tempStack.empty());
}


// Finding Min element in a stack


void push(int x)
{
	if(s.empty())
	{
		int minele = x;
		s.push(x);
		return;
	}

	if(x < minele)
	{
		s.push(2*x-minele);
		minele = x;
	}
	else
		s.push(x);

}

void pop()
{
	int y = s.top();
	s.pop();

	if(y < minele)
	{
		minele = 2*minele-y;
	}
}