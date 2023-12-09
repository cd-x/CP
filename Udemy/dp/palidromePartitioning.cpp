//https://leetcode.com/problems/palindrome-partitioning/

class Solution {
    bool isPal(string s){
        string tmps = s;
        reverse(s.begin(), s.end());
        return tmps == s;
    }
public:
    vector<vector<string>> partition(string s) {
        if(s.empty()) return {{}};
        string tmp = "";
        vector<vector<string>> res;
        for(int i=0;i<s.size();i++){
            tmp.push_back(s[i]);
            if(isPal(tmp)){
                vector<vector<string>> sub = partition(s.substr(i+1));
                for(vector<string> ans: sub){
                    ans.insert(ans.begin(), tmp);
                    res.push_back(ans);
                }
            }
        }
        return res;
    }
};
