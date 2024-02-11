class LRUCache {
private:
    list<int> li; // most recent element at front
    unordered_map<int,int> hm_kv;
    unordered_map<int,list<int>::iterator> hm_ki;
    int N;
public:
    LRUCache(int capacity) {
        N = capacity;
    }
    
    int get(int key) {
        
        if (hm_kv.find(key)==hm_kv.end()) return -1;
        int tmp = hm_kv[key];
        li.erase(hm_ki[key]);
        li.push_front(key);
        hm_ki[key] = li.begin();
        return tmp;
    }
    
    void put(int key, int value) 
    {
        if (hm_kv.find(key)!=hm_kv.end())
        {
            hm_kv[key] = value;
            li.erase(hm_ki[key]);
            li.push_front(key);
            hm_ki[key] = li.begin();
        }
        else if (N > 0)
        {
            li.push_front(key);
            hm_kv.emplace(key,value);
            hm_ki.emplace(key,li.begin());
            N--;
        }
        else if (N==0)
        {
            int tmp = li.back();
            li.erase(hm_ki[tmp]);
            hm_kv.erase(tmp);
            hm_ki.erase(tmp);
            li.push_front(key);
            hm_kv.emplace(key,value);
            hm_ki.emplace(key,li.begin());
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */