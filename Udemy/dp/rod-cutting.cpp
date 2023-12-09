#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> p32;
typedef pair<ll, ll> p64;
typedef pair<double, double> pdd;
ll MOD = 1000000007;
double eps = 1e-12;

unordered_map<long int, int> dp;
int minCost(vector<int>& cuts, int l, int h, int i, int j){
    if(i>j) return 0;
    int hash = l + h*17;
    if(dp.find(hash) != dp.end()) return dp[hash];
    int ans = INT_MAX;
    int mincut=-1;
    for(int x= i;x<=j;x++){
        int cost1= minCost(cuts, l, cuts[x], i, x-1);
        int cost2 = minCost(cuts, cuts[x], h, x+1, j);
        int cost = cost1 + cost2 + h-l;
        if(cost<ans){
        	ans = cost;
        	mincut = cuts[x];
        }
    }
    cout<<"mincut: "<<mincut<<" cost: "<<ans<<endl;
    return dp[hash] = ans;
}
int main()
{
  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
  	// -----input-------
  	int n; cin>>n;
  	vector<int> cuts;
  	int x; while(cin>>x) cuts.push_back(x);
  	cout<<minCost(cuts, 0,n, 0, cuts.size()-1);
    // ------output-----
  return 0;
}