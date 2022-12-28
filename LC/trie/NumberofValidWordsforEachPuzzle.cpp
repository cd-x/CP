//LC ID: 1178

/**
Solution 1 is using a trie to hash all the words and count using dfs only when word
has satisfied the condition that it contains first letter
*/

class Solution {
    struct node{
        int cnt;
        node* children[26] = {nullptr};
    };
    string cleanstr(string s){
        vector<bool> hash(26, false);
        for(char& ch: s) hash[ch-'a'] = true;
        string res ="";
        for(char ch = 'a';ch<='z';ch++) if(hash[ch-'a']) res.push_back(ch);
        return res;
    }
    void insert(node* root, string s){
        for(char& ch: s){
            if(!root->children[ch-'a'])
                root->children[ch-'a'] = new node();
            root = root->children[ch-'a'];
        }
        root->cnt++;
    }
    int dfs(node* root, string puzzle, char first, bool hasFirst){
        if(!root) return 0;
        int res = hasFirst? root->cnt : 0;
        for(char& ch: puzzle){
            if(root->children[ch-'a'])
                res += dfs(root->children[ch-'a'], puzzle, first, hasFirst | (ch == first));
        }
        return res;
    }
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        node* root = new node();
        for(string& w : words){
            string tmp = cleanstr(w);
            if(tmp.size()<=7)
                insert(root, tmp);
        }
        vector<int> res;
        for(string& s: puzzles){
            char first = s[0];
            string tmp = cleanstr(s);
            int ans = dfs(root, tmp, first, false);
            res.push_back(ans);
        }
        return res;
    }
};

/**

Below solution 2 is very important to understand bitmasking 
Here bitmasking is used to generate all possible permutation of puzzle
string. As what happens when you do 
while(submask>0)
	submask = (submask-1)&mask
it generates all values when each set bit in original mask will be either set or unset
this way we will have all permutation of string 
*/

class Solution {
    int getmask(string s){
        int ans = 0;
        for(char& ch: s) ans |= 1<<(ch-'a');
        return ans;
    }
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        unordered_map<int,int>ump;
        for(string& w: words) ump[getmask(w)]++;
        vector<int> res;
        for(string s: puzzles){
            int firstletter = 1<<(s[0]-'a');
            int ans= ump[firstletter];
            int mask = getmask(s.substr(1));
            for(int sub = mask;sub>0;sub = (sub-1)&mask)
                ans += ump[(sub|firstletter)];
            res.push_back(ans);
        }
        return res;
    }
};
