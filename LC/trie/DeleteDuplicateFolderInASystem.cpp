// LC ID: 1948
class Solution {
    struct node{
        string folder;
        map<string,node*> subfolder;
        bool duplicate = false;
        node(): folder(""){}
        node(string s): folder(s){}
    };
    void construct(node* root, vector<string>& path){
        for(string& s: path){
            if(!root->subfolder[s])
                root->subfolder[s] = new node(s);
            root = root->subfolder[s];
        }
    }
    unordered_map<string, node*> vis;
    string markDuplicates(node* root){
        if(!root) return NULL;

        string children;
        for(auto& [_, nbr]: root->subfolder)
            children += markDuplicates(nbr);
        if(!children.empty()){
            if(vis.find(children) != vis.end())
                vis[children]->duplicate = root->duplicate = true;
            else
                vis[children] = root;
        }
        return "(" + root->folder + children+ ")";
    }
    vector<vector<string>> ans;
    vector<string> path;
    void deletePaths(node* root){
        if(root->duplicate) return;
        if(!(root->folder).empty())
            path.push_back(root->folder);
        if(!path.empty())
            ans.push_back(path);
        for(auto& [_, nbr]: root->subfolder)
            deletePaths(nbr);
        if(!path.empty())
            path.pop_back();
    }
public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        vis.clear(); ans.clear(); path.clear();
        node* root = new node();
        for(vector<string>& path: paths) construct(root, path);
        markDuplicates(root);
        deletePaths(root);
        return ans;
    }
};
