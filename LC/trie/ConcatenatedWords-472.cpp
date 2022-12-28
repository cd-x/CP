//LC ID: 472

/**

As the string length is 30 only so Trie search will be constant
idea is to sort on length of each word and ques says each word is unique
so there will always be at least 2 words to form cur word if it can be formed.
So we can create trie at runtime after checking if that word exist using dfs.
It will branch off whenever we find any word in the trie and search substring.

*/

class Solution {
    struct node{
        bool eow;
        node* children[26] = {nullptr};
    };
    node* root;
    bool has2word(node* cur, int i, string s){
        if(i>=s.size()) return cur->eow;
        if(cur->children[s[i]-'a']){
            cur = cur->children[s[i] - 'a'];
            if(cur->eow && has2word(root, i+1, s)) return true;
            else return has2word(cur, i+1, s);
        }
        return false;
    }

    void insert(node* cur, string s){
        for(char& ch: s){
            if(!cur->children[ch-'a'])
                cur->children[ch-'a'] = new node();
            cur = cur->children[ch-'a'];
        }
        cur->eow = true;
    }
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        sort(begin(words), end(words),[](string& s1, string& s2){
            if(s1.size() == s2.size()) return s1<s2;
            return s1.size() < s2.size();
        });
        vector<string> res;
        root = new node();
        for(string& s: words){
            if(has2word(root, 0,s))
                res.push_back(s);
            insert(root, s);
        }
        return res;
    }
};
