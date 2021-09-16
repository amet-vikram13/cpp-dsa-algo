#include <iostream>
using namespace std;

int main()
{
    int g,n,m,x,input,sum,ptrA,ptrB,flag,i,j,moves,tempmove;
    cin>>g;
    
    while(g--)
    {    
        
        cin>>n>>m>>x;
        
        int A[n];
        int B[m];
        
        ptrA = n; ptrB = m;
        flag = 1; sum=0;

        
        for(i=0;i<n;i++)
        {
        	cin>>input;
        	sum += input;
        	if(sum > x && flag==1)
        	{
        		ptrA = i;
        		flag = 0;
        	}
        	A[i] = sum;

        }

        sum = 0; flag = 1;

        for(j=0;j<m;j++)
        {
            cin>>input;
        	sum += input;
        	if(sum > x && flag==1)
        	{
        		ptrB = j;
        		flag = 0;
        	}
        	B[j] = sum;
        }
        
        cout<<endl;

        for(i=0;i<n;i++)
        	cout<<A[i]<<" ";

        cout<<endl;

        for(j=0;j<m;j++)
        	cout<<B[j]<<" ";

        cout<<endl;	
		

		i = 0; 
        j = 0; 
        moves=0;
        sum = 0;

        if(ptrA==ptrB)
        {
        	if(A[ptrA-1]+B[ptrB-1] <= x)
	        	cout<<ptrA+ptrB<<endl;
	        else
	        {
	        	if(A[ptrA-1] <= B[ptrB-1])
	        	{
	        		moves = ptrA;
	        		sum = A[ptrA-1];
	        		j = 0;
	        		while(j<ptrB)
			        {
			       		if(j==0)
			       		{
			       			if(sum+B[j] <= x)
			       				sum += B[j];
			       			else
			       				break;
			       		}
			       		else
			       		{
			       			if(sum+B[j]-B[j-1] <= x)
			       				sum += B[j]-B[j-1];
			       			else
			       				break;
			       		}

			       		moves++;
			       		j++;
			    	}
			    }
			    else if(B[ptrB-1] < A[ptrA-1])
			    {
			    	moves = ptrB;
			    	sum = B[ptrB-1];
			    	i = 0;
			    	while(i<ptrA)
	        		{
			       		if(i==0)
			       		{
			       			if(sum+A[i] <= x)
			       				sum += A[i];
			       			else
			       				break;
			       		}
			       		else
			       		{
			       			if(sum+A[i]-A[i-1] <= x)
			       				sum += A[i]-A[i-1];
			       			else
			       				break;
			       		}
			       		moves++;
			       		i++;
			        }
			    }

			    cout<<moves<<endl;
        	}
        
        }
        else if(ptrA!=ptrB)
        {
        	if(ptrA > ptrB)
        	{
        	    if(A[ptrA-1] <= B[ptrB-1])   
                {
                    moves = ptrA;
                    sum = A[ptrA-1];
                    j = 0;
                    while(j<ptrB)
                    {	

                        if(j==0)
                        {
                            if(sum+B[j] <= x)
                                sum += B[j];
                            else
                                break;
                        }
                        else
                        {
                            if(sum+B[j]-B[j-1] <= x)
                                sum += B[j]-B[j-1];
                            else
                                break;
                        }

                        moves++;
                        j++;
                    }
                }
                else if(A[ptrA-1] > B[ptrB-1])
                {
                    tempmove = ptrA;
                    
                    moves = ptrB;
                    sum = B[ptrB-1];
                    i = 0;
                    while(i<ptrA)
                    {
                        if(i==0)
                        {
                            if(sum+A[i] <= x)
                                sum += A[i];
                            else
                                break;
                        }
                        else
                        {
                            if(sum+A[i]-A[i-1] <= x)
                                sum += A[i]-A[i-1];
                            else
                                break;
                        }
                        moves++;
                        i++;
                    }
                    
                    if(tempmove >= moves)
                    {
                    	moves = tempmove;
                    	sum = A[ptrA-1];
                    	j = 0;
                    	while(j<ptrB)
	                    {
	                        if(j==0)
	                        {
	                            if(sum+B[j] <= x)
	                                sum += B[j];
	                            else
	                                break;
	                        }
	                        else
	                        {
	                            if(sum+B[j]-B[j-1] <= x)
	                                sum += B[j]-B[j-1];
	                            else
	                                break;
	                        }

	                        moves++;
	                        j++;
	                    }
                    }
                }
		    }
		    else if(ptrB > ptrA)
		    {
                if(B[ptrB-1] <= A[ptrA-1])    
                {
                    moves = ptrB;
                    sum = B[ptrB-1];
                    i = 0;
                    while(i<ptrA)
                    {
                        if(i==0)
                        {
                            if(sum+A[i] <= x)
                                sum += A[i];
                            else
                                break;
                        }
                        else
                        {
                            if(sum+A[i]-A[i-1] <= x)
                                sum += A[i]-A[i-1];
                            else
                                break;
                        }
                        moves++;
                        i++;
                    }
                }
                else if(B[ptrB-1] > A[ptrA-1])
                {
                    tempmove = ptrB;
                    
                    moves = ptrA;
                    sum = A[ptrA-1];
                    j = 0;
                    while(j<ptrB)
                    {
                        if(j==0)
                        {
                            if(sum+B[j] <= x)
                                sum += B[j];
                            else
                                break;
                        }
                        else
                        {
                            if(sum+B[j]-B[j-1] <= x)
                                sum += B[j]-B[j-1];
                            else
                                break;
                        }

                        moves++;
                        j++;
                    }
                    
                    if(tempmove >= moves)
                    {
                    	moves = tempmove;
                    	sum = B[ptrB-1];
                    	i = 0;
                    	while(i<ptrA)
	                    {
	                        if(i==0)
	                        {
	                            if(sum+A[i] <= x)
	                                sum += A[i];
	                            else
	                                break;
	                        }
	                        else
	                        {
	                            if(sum+A[i]-A[i-1] <= x)
	                                sum += A[i]-A[i-1];
	                            else
	                                break;
	                        }
	                        moves++;
	                        i++;
	                    }

                    }
                    
                }
		    }

		    cout<<moves<<endl;
		} 

	}
    
	
	return 0;
}