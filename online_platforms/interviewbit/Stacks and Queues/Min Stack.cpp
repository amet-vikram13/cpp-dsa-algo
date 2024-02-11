stack<long long int> st;
long long int min_ele;

MinStack::MinStack() {
	
	while(!st.empty())
		st.pop();
}

void MinStack::push(int x)
{
	if (st.empty())
	{
		st.push((long long int)x);
		min_ele = (long long int)x;
	}
	else if (x < min_ele)
	{
		st.push((long long int)(2*x-min_ele));
		min_ele = (long long int)x;
	}
	else
		st.push((long long int)x);
}

void MinStack::pop()
{
	if (st.empty()) return;
	long long int x = st.top();
	st.pop();
	if (x < min_ele)
		min_ele = 2*min_ele-x;
	return;
}

int MinStack::top()
{
	if (st.empty()) return -1;
	long long int x = st.top();
	if (x < min_ele)
		x = min_ele;
	return (int)x;
}

int MinStack::getMin()
{
	if (st.empty()) return -1;
	return (int)min_ele;
}