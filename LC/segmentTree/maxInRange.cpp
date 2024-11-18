#include<bits/stdc++.h>
using namespace std;

class SegTree{
	int size;
	vector<int> tree;
	vector<int> nums;
	void build(int index, int lo, int hi){
		if(lo == hi){
			tree[index] = nums[lo];
			return;
		}
		int mid = (lo + hi)/2;
		build(2*index+1, lo, mid);
		build(2*index+2, mid+1, hi);
		tree[index] = max(tree[2*index+1], tree[2*index+2]);
	}
	int query(int index, int l, int r, int ql, int qr){
		if(ql<=l && r<=qr) return tree[index];
		if(ql>r || qr<l) return INT_MIN;
		int mid = (l + r)/2;
		int lmax = query(2*index+1, l, mid, ql, qr);
		int rmax = query(2*index+2, mid+1, r, ql, qr);
		return max(lmax, rmax);
	}
public:
	SegTree(vector<int> arr){
		nums = arr;
		size = arr.size();
		tree.resize(4*size);
		build(0,0,size - 1);
	}

	int query(int lo, int hi){
		return query(0, 0, size-1, lo, hi);
	}

};

int main(){
	vector<int> arr = {2,4,5,2,1,0,3,3,3,9,7,8};
	SegTree* tree = new SegTree(arr);
	cout<<tree->query(3,11);
	delete tree;
}