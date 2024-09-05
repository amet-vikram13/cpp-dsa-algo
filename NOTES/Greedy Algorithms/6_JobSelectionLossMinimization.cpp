#include <bits/stdc++.h>
using namespace std;

/*
We are given a sequence of N goods of production numbered from 1 to N. Each good has a volume 
denoted by (Vi). The constraint is that once a good has been completed its volume starts decaying 
at a fixed percentage (P) per day. All goods decay at the same rate and further each good take 
one day to complete.
We are required to find the order in which the goods should be produced so that overall volume 
of goods is maximized.

Since this is an optimization problem, we can try to solve this problem by using a greedy algorithm. 
On each day we make a selection from among the goods that are yet to be produced. Instead of trying to 
maximize the volume, we can also try to minimize the losses. Since the total volume that can be obtained 
from all goods is also constant, if we minimize the losses we are guaranteed to get the optimum answer.

Now consider any good having volume V
Loss after Day 1: PV
Loss after Day 2: PV + P(1-P)V or V(2P-P^2)
Loss after Day 3: V(2P-P^2) + P(1 – 2P + P^2)V or V(3P – 3P^2 + P^3)

As the day increases the losses too increase. So the trick would be to ensure that the goods are not kept 
idle after production. Further, since we are required to produce at least one job per day, we should perform 
low volume jobs, and then perform the high volume jobs. This strategy works due to two factors :-
	1) High Volume goods are not kept idle after production.
	2) As the volume decreases the loss per day too decreases, so for low volume goods the losses become 
	   negligible after a few days.

So in order to obtain the optimum solution we produce the larger volume goods later on. For the first day 
select the good with least volume and produce it. Remove the produced good from the list of goods. For the 
next day repeat the same. Keep repeating while there are goods left to be produced.

Algorithm –

Step 1: Add all the goods to a min-heap       
Step 2: Repeat following steps while Queue is not empty
        Extract the good  at the head of the heap
        Print the good
        Remove the good from the heap
        [END OF LOOP]
Step 4: End
*/
void optimumSequencJobs(int V[],double P,int N)
{
	int j = 1;
	N = N-1;
	double result = 0;

	// Create a min-heap (priority queue)
	priority_queue<int,vector<int>,greater<int> > Queue;

	// Add all goods to the the Queue
    for (int i = 1; i <= N; i++) 
        Queue.push(V[i]);

    // Pop Goods from Queue as long as it is not empty
    while (!Queue.empty()) 
    {
 
        // Print the good
        cout << Queue.top() << " ";
 
        // Add the Queue to the vector
        // so that total voulme can be calculated
        V[j++] = Queue.top();
        Queue.pop();
    }

    // Calclulating volume of goods left when all
    // are produced. Move from right to left of 
    // sequence multiplying each volume by 
    // increasing powers of 1 - P starting from 0
    for (int i = N; i >= 1; i--) 
        result += pow((1 - P), N - i)*V[i];  

    cout<<endl<<result<<endl;
}

int main()
{
	int V[] = {-1, 3, 5, 4, 1, 2, 7, 6, 8, 9, 10 };
	int N = 11;

	// 10% loss per day
    double P = 0.10;
 
    optimumSequencJobs(V, P, N);
	
	return 0;
}