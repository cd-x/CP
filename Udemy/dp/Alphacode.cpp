#include<bits/stdc++.h>
using namespace std;

vector<long long> dp;
long long recur(int i, string& s){
	if(dp[i]>0) return dp[i];
	if(i>=s.size()) return 1;
	long long ans= 0;
	if(s[i]>'0' && s[i]<='9'){
		ans += recur(i+1, s);
	}
	if(i+1<s.size() && (s[i]=='1' || (s[i]=='2' && s[i+1]<'7'))){
		ans+= recur(i+2, s);
	}
	return dp[i] = ans;
}
int main(){
	while(true){
		string s; cin>>s;
		if(s=="0") break;
		dp.clear();
		dp.resize(s.size(), -1);
		cout<<recur(0,s)<<"\n";
	}
}