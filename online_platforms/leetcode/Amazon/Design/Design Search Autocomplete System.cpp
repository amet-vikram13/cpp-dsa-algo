struct Node
{
    int count;
    Node* next[27];
    Node()
    {
        count = -1;
        for(int i=0;i<27;i++)
            next[i] = NULL;
    }
    
};

class Trie
{
    private:
        Node* root;
        unordered_map<string,int> hm;
    
        int charAtd(string txt,int d)
        {
            if (d < txt.size())
            {
                if (txt[d]!=' ') return txt[d]-'a';
                return 26;
            }
            return -1;
        }
    
        char intTochar(int d)
        {
            if (d < 26) return 'a'+d;
            return ' ';
        }
    
        Node* _push(Node* x,int d,string txt,int val)
        {
            if (x==NULL) x = new Node();
            if (d == txt.size())
            {
                
                if (val != -1)
                    x->count = val;
                else if (x->count == -1)
                    x->count = 1;
                else
                    x->count += 1;
                return x;
            }
            int c = charAtd(txt,d);
            x->next[c] = _push(x->next[c],d+1,txt,val);
            return x;
        }
    
        void searchTree(Node* x,string rec)
        {
            bool all_child_null = true;
            
            for(int i=0;i<27;i++)
            {
                if (x->next[i]!=NULL)
                {
                    all_child_null = false;
                    rec.push_back(intTochar(i));
                    searchTree(x->next[i],rec);
                    rec.pop_back();
                }
            }
            
            if (all_child_null || x->count!=-1)
            {
                if (hm.size() == 3)
                {
                    hm.emplace(rec,x->count);
                    unordered_map<string,int>::iterator it = next(hm.begin(),1);
                    unordered_map<string,int>::iterator del = hm.begin();   
                    for(;it!=hm.end();it++)
                    {
                        if (it->second <= del->second)
                        {
                            if (it->second < del->second)
                                del = it;
                            else if (it->first.compare(del->first) > 0)
                                del = it;
                        }
                    }
                    hm.erase(del);
                }
                else
                    hm.emplace(rec,x->count);
                
            }
        }
    
    public:
        Trie()
        {
            root = NULL;   
        }
    
        void push(string txt,int val)
        {
            root = _push(root,0,txt,val);
        }
    
        vector<string> getHot(string prefix)
        {
            vector<string> ans;
            
            int ptr = 0; Node* tmp = root;
            while(ptr<prefix.size() && tmp!=NULL)
                tmp = tmp->next[charAtd(prefix,ptr++)];
            
            if (tmp == NULL) return ans;
            
            string rec = prefix;
            searchTree(tmp,rec);
            
            unordered_map<string,int>::iterator it = next(hm.begin(),1);
            unordered_map<string,int>::iterator max_it = hm.begin();
            for(;it!=hm.end();it++)
            {
                if (it->second >= max_it->second)
                {
                    if      (it->second > max_it->second)
                        max_it = it;
                    else if (it->first.compare(max_it->first) < 0)
                        max_it = it;
                }
            }
            ans.push_back(max_it->first); hm.erase(max_it);
            
            if (hm.empty()) return ans;
            
            it = next(hm.begin(),1);
            max_it = hm.begin();
            for(;it!=hm.end();it++)
            {
                if (it->second >= max_it->second)
                {
                    if      (it->second > max_it->second)
                        max_it = it;
                    else if (it->first.compare(max_it->first) < 0)
                        max_it = it;
                }
            }
            ans.push_back(max_it->first); hm.erase(max_it);
            
            if (hm.empty()) return ans;
            
            ans.push_back(hm.begin()->first);
            hm.clear();
            return ans;
        }
};


class AutocompleteSystem { 
private:
    string prefix;
    Trie* tr;
    
public:
    
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        prefix = "";
        tr = new Trie;
        for(int i=0;i<times.size();i++)
            tr->push(sentences[i],times[i]);
    }
    
    vector<string> input(char c) {
        if (c == '#')
        {
            vector<string> e;
            tr->push(prefix,-1);
            prefix = "";
            return e;
        }
        prefix.push_back(c);
        return tr->getHot(prefix);
    }
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */