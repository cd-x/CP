//LC ID: 1803

class Solution {
    struct node{
        int cnt = 0;
        node* children[2] = {nullptr};
    };
    int size;
    void insert(node* root, int x){
        for(int i = size-1;i>=0;i--){
            int bit = (x>>i)&1;
            if(!root->children[bit])
                root->children[bit] = new node();
            root = root->children[bit];
            root->cnt = root->cnt + 1;
        }
    }
    int count(node* root, int E, int K){
        int res = 0;
        for(int i = size-1;i>=0 && root;i--){
            int bitE = E>>i&1;
            int bitK = K>>i&1;
            if(bitK){
                if(root->children[bitE]) res += root->children[bitE]->cnt;
                root = root->children[1-bitE];
            }else{
                root = root->children[bitE];
            }
        }
        return res;
    }
public:
    int countPairs(vector<int>& nums, int low, int high) {
        //int mxe = *max_element(begin(nums), end(nums));
        // global init
        int res = 0;
        size= 16;//log2(mxe) +1;
        node* root = new node();
        for(int& x: nums){
            res += count(root, x, high+1) -count(root, x, low);
            insert(root, x);
        }
        return res;
    }
};
