#include<bits/stdc++.h>
using namespace std;

class SegTree{
	vector<int> tree;
	vector<int> nums;
	int n;

	void build(int index, int l, int r){
		if(l==r){
			tree[index] = nums[l];
		 	return;
		}
		int mid = (l+r)/2;
		build(2*index+1, l, mid);
		build(2*index+2, mid+1, r);
		tree[index] = tree[2*index+1] + tree[2*index +2];
	}
	int query(int index, int l, int r, int ql, int qr){
		if(ql<=l && r<=qr) return tree[index];
		if(ql>r || qr<l) return 0;
		int mid = (l+r)/2;
		int lsum = query(2*index+1, l, mid, ql,qr);
		int rsum = query(2*index+2, mid+1, r, ql, qr);
		return lsum + rsum;
	}
	void update(int index, int val, int internal_index, int l, int r){
		if(index<l || index>r) return;
		if(l==r){
			tree[internal_index] += val;
			return;
		} 
		int mid = (l+r)/2;
		update(index, val, 2*internal_index+1, l, mid);
		update(index, val, 2*internal_index+2, mid+1, r);
		tree[internal_index] = tree[2*internal_index+1] + tree[2*internal_index+2];
	}
public:
	SegTree(vector<int>& arr){
		n= arr.size();
		nums = arr;
		tree.resize(4*n);
		build(0,0,n-1);
	}
	int getSum(int left, int right){
		return query(0, 0, n-1, left, right);
	}
	void addVal(int index, int val){
		update(index, val, 0, 0, n-1);
		nums[index] += val;
	}
};

int main(){
	vector<int> arr ={2,1,3,4,2,3,3,3,6,7,9,0};
	SegTree* tree = new SegTree(arr);
	cout<<tree->getSum(4,6)<<endl;
	tree->addVal(4,3);
	cout<<tree->getSum(4,6)<<endl;
	delete tree;
	return 0;
}