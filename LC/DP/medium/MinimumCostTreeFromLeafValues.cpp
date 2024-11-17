//LC ID: 1130

class Solution {
    struct hash_pair{
        template <class T1, class T2>
        size_t operator()(const pair<T1, T2>& p) const{
            auto h1 = hash<T1>{}(p.first);
            auto h2 = hash<T2>{}(p.second);
            return h1 == h2? h1 : h1^h2;
        }
    };
    typedef pair<int,int> pii;
    unordered_map<pii, pii, hash_pair> ump;
    pii helper(int l, int r, vector<int>& arr){
        if(l==r) return {0, arr[l]};
        if(ump.find({l,r}) != ump.end()) return ump[{l,r}];
        int ans = INT_MAX, MXLEAF = -1;
        for(int i=l;i<r;i++){
            auto [lsum, lmx]  = helper(l,i,arr);
            auto [rsum, rmx] = helper(i+1, r, arr);
            ans = min(ans, lsum + rsum + lmx*rmx);
            MXLEAF = max(MXLEAF, max(lmx, rmx));
        }
        return ump[{l,r}] = {ans, MXLEAF};
    }
public:
    int mctFromLeafValues(vector<int>& arr) {
        return helper(0,arr.size()-1, arr).first;
    }
};