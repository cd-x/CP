//LC ID: 1707

class Solution {
    struct node{
        node* children[2] = {nullptr};
    };
    int size;
    void insert(node* root, int x){
        for(int i = size-1;i>=0;i--){
            int bit = x>>i&1;
            if(!root->children[bit])
                root->children[bit] = new node();
            root = root->children[bit];
        }
    }
    int maxXor(node* root, int E){
        int ans = 0;
        for(int i = size-1;i>=0;i--){
           int bitE = E>>i&1;
           if(root->children[1-bitE]){
               root = root->children[1-bitE];
               ans  =  (ans<<1) + 1-bitE;
           }else{
               root = root->children[bitE];
               ans = (ans<<1) + bitE;
           }
           if(!root) return -1;
        }
        return ans^E;
    }
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        size = 32;
        node* root = new node();
        vector<vector<int>> tmp; int len = 0, num_len = nums.size();
        for(auto& q: queries)
            tmp.push_back({q[0], q[1], len++});
        
        //sorting queries gives us advantage of getting max values out of already present
        //lesser items than upper cap, as we will be insering nums at runtime. 
        sort(begin(nums), end(nums));
        sort(begin(tmp), end(tmp), [](auto& v1, auto& v2){
            return v1[1]<v2[1];
        });

        vector<int> res(len);
        int num_idx = 0;
        for(auto& q: tmp){
            int E = q[0], K = q[1], idx = q[2];
            while(num_idx<num_len && nums[num_idx]<=K) insert(root, nums[num_idx++]);
            int ans = maxXor(root, E);
            res[idx] = ans;
        }
        return res;
    }
};
