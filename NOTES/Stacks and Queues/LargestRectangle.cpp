#include <iostream>
#include <stack>
using namespace std;

int main()
{
	int n,input,curr,area,max=-1,Lflag,Rflag; cin>>n;
	stack<int> left;
	stack<int> right;
	

	for(int i=0;i<n;i++)
	{
		cin>>input;
		left.push(input);
	}

	cout<<endl;
	
	int count,temp;
	
	for(int i=1;i<2;i++)
	{
	    /* loop input i = 0 */
		right.push(left.top()); left.pop();
		max = 0;
	    Lflag = -1; 
        Rflag = -1;
        count = 0;
		curr = left.top(); area = curr;


        
        
        left.pop();
        if(!left.empty())
        {
            while(curr==left.top())
            {
                Lflag++;
                left.pop();
                count++;
                if(left.empty())
            		break;
            }
            
        }
        left.push(curr);

        /* CODE CHECKING 
		stack<int> l,r;
		cout<<"left :";
		while(!left.empty())
		{
		    cout<<left.top()<<" ";
		    l.push(left.top());
		    left.pop();
		}
		while(!l.empty())
		{
		    left.push(l.top());
		    l.pop();
		}
		cout<<endl<<"right :";
		while(!right.empty())
		{
		    cout<<right.top()<<" ";
		    r.push(right.top());
		    right.pop();
		}
		while(!r.empty())
		{
		    right.push(r.top());
		    r.pop();
		}
		cout<<endl<<"i : "<<i<<" curr : "<<curr<<" Lflag : "<<Lflag<<" Rflag : "<<Rflag<<" count : "<<count<<endl<<endl;
		//*/
		
        
        
        
        if(!right.empty())
        {
            while(curr==right.top());
            {
                count++;
                Rflag++;
                right.pop();
                if(right.empty())
                {
                	break;
                }
            }
        }

        //* CODE CHECKING 
		stack<int> l,r;
		cout<<"left :";
		while(!left.empty())
		{
		    cout<<left.top()<<" ";
		    l.push(left.top());
		    left.pop();
		}
		while(!l.empty())
		{
		    left.push(l.top());
		    l.pop();
		}
		cout<<endl<<"right :";
		while(!right.empty())
		{
		    cout<<right.top()<<" ";
		    r.push(right.top());
		    right.pop();
		}
		while(!r.empty())
		{
		    right.push(r.top());
		    r.pop();
		}
		cout<<endl<<"i : "<<i<<" curr : "<<curr<<" Lflag : "<<Lflag<<" Rflag : "<<Rflag<<" count : "<<count<<endl<<endl;
		//
		/*
		
        
        if(!right.empty())
		{
			while(right.top() >= curr)
			{	
                count++;
                left.push(right.top());
                right.pop();
				if(right.empty())
                    break;
			}	
		}
	
		
		while(left.top() != curr)
		{	
			right.push(left.top());
            left.pop();
			if(left.empty())
                break;
        }
		while(Rflag--)
            right.push(curr);
		
        
        right.push(left.top()); left.pop();

   		
   		if(left.empty() && Lflag==0)
		{	
			area *= (count+1);
			if(area > max)
				max = area;
			break;
		}
		
	
		
        while(left.top() >= curr)
		{	
			count++;
			right.push(left.top());
            left.pop();
			if(left.empty())
		          break;
		}
	
		while(right.top() != curr)
		{	
			left.push(right.top());
            right.pop();
			if(right.empty())
			     break;
		}
        while(Lflag--)
            left.push(curr);
        
        
        
        area *= (count+1);
		if(area > max)
			max = area;
		
		/* CODE CHECKING 
		//stack<int> l,r;
		cout<<"left :";
		while(!left.empty())
		{
		    cout<<left.top()<<" ";
		    l.push(left.top());
		    left.pop();
		}
		while(!l.empty())
		{
		    left.push(l.top());
		    l.pop();
		}
		cout<<endl<<"right :";
		while(!right.empty())
		{
		    cout<<right.top()<<" ";
		    r.push(right.top());
		    right.pop();
		}
		while(!r.empty())
		{
		    right.push(r.top());
		    r.pop();
		}
		cout<<endl<<"i : "<<i<<" curr : "<<curr<<" Lflag : "<<Lflag<<" Rflag : "<<Rflag<<" count : "<<count<<endl<<endl;
		*/

	}
	
	cout<<max<<endl;
}