class MedianFinder {
public:
    /** initialize your data structure here. */
    priority_queue<int> max_pq;
    priority_queue<int,vector<int>,greater<int> > min_pq;
    
    MedianFinder() {
        while(!max_pq.empty())
            max_pq.pop();
        while(!min_pq.empty())
            min_pq.pop();
    }
    
    void addNum(int num) 
    {
        
        if (max_pq.size() == min_pq.size())
        {
            if (max_pq.empty())
                max_pq.push(num);
            else
            {
                if (num < min_pq.top())
                    max_pq.push(num);
                else
                {
                    max_pq.push(min_pq.top());
                    min_pq.pop();
                    min_pq.push(num);
                }
            }
        }
        else
        {
             if (num < max_pq.top())
             {
                 min_pq.push(max_pq.top());
                 max_pq.pop();
                 max_pq.push(num);
             }
             else
                 min_pq.push(num);
        }
    }
    
    double findMedian() {
        double ans;
        if (max_pq.size() == min_pq.size())
        {
            ans = ((double)max_pq.top()+(double)min_pq.top())/2.0L;
        }
        else
            ans = (double)max_pq.top();
        return ans;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */