class MinStack {
public:
    /** initialize your data structure here. */
    stack<long long int> st;
    long long int min_ele;
    
    MinStack() 
    {
        
        while(!st.empty())
            st.pop();
    }
    
    void push(int x) 
    {
        if      (st.empty())
        {
            st.push((long long int)x);
            min_ele = (long long int)x;
        }
        else if (x < min_ele)
        {
            st.push((long long int)2*x-min_ele);
            min_ele = (long long int)x;
        }
        else
            st.push((long long int)x);
    }
    
    void pop() {
        long long int x = st.top();
        st.pop();
        if (x < min_ele)
            min_ele = 2*min_ele-x;
    }
    
    int top() {
        long long int x = st.top();
        if (x < min_ele)
            x = min_ele;
        return (int)x;
    }
    
    int getMin() {
        return min_ele;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */