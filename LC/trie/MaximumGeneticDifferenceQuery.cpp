//LC ID: 1938

/**

The key idea here was to group each node in query:[node, val], and do dfs traversal on current trie
(as we are building trie at runtime so it contains only nodes that are in path to root).
we also maintain count to insert or delete that node from trie as we are making a check (go if cnt>0)

*/

class Solution {
    struct node{
        int cnt;
        node* children[2] = {nullptr};
    };
    unordered_map<int, vector<pair<int,int>>> ump;
    vector<int> res;
    vector<vector<int>> graph;
    int size;
    void dfs(int s, node* root){
        insert(root, s);
        for(int& nbr: graph[s])
            dfs(nbr, root);
        for(auto& [x, i]: ump[s]){
            res[i] = getmax(root, x);
        }
        deleteval(root, s);
    }

    void insert(node* root, int E){
        for(int i=size-1;i>=0;i--){
            int bitE = E>>i&1;
            if(!root->children[bitE])
                root->children[bitE] = new node();
            root = root->children[bitE];
            root->cnt++;
        }
    }
    void deleteval(node* root, int E){
        for(int i=size-1;i>=0;i--){
            int bitE = E>>i&1;
            root = root->children[bitE];
            root->cnt--;
        }
    }

    int getmax(node* root, int E){
        int ans = 0;
        for(int i=size-1;i>=0;i--){
            int bitE = E>>i&1;
            if(root->children[1-bitE] && (root->children[1-bitE])->cnt>0){
                root = root->children[1-bitE];
                ans = (ans<<1) + 1-bitE;
            }else{
                root = root->children[bitE];
                ans = (ans<<1) + bitE;
            }
        }
        return ans^E;
    }
public:
    vector<int> maxGeneticDifference(vector<int>& par, vector<vector<int>>& q) {
        size = 32;
        int len = q.size();
        res.clear(); res.resize(len);
        for(int i=0;i<len;i++)
            ump[q[i][0]].push_back({q[i][1], i});
        int parlen = par.size();
        graph.resize(parlen);
        int root_idx; 
        for(int i=0;i<parlen;i++){
            if(par[i]<0) root_idx = i;
            else graph[par[i]].push_back(i);
        }
        node* root = new node();
        dfs(root_idx, root);
        return res;
    }
};
