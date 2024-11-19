#include <bits/stdc++.h>
using namespace std;

class SegmentTree{
	vector<int> tree;
	vector<int> nums;
	vector<int> propagate;
	int size;

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
	void update(int ql, int qr, int val, int internal_index, int l, int r){
		int& pending_update = propagate[internal_index];
		if(pending_update){
			tree[internal_index] += pending_update*(r-l+1);
			if(l!=r){
				propagate[2*internal_index+1] += pending_update;
				propagate[2*internal_index+2] += pending_update;
			}
			pending_update = 0;
		}
		if(ql>r || qr<l) return;
		if(ql<=l && r<=qr){
			tree[internal_index] += val*(r-l+1);
			if(l!=r){
				propagate[2*internal_index+1] += val;
				propagate[2*internal_index+2] += val;
			}
			return;
		}
		int mid = (l+r)/2;
		update(ql, qr, val, 2*internal_index+1, l, mid);
		update(ql, qr, val, 2*internal_index+2, mid+1, r);
		tree[internal_index] = tree[2*internal_index+1] + tree[2*internal_index+2];
	}
public:
	SegmentTree(vector<int>& arr){
		size = arr.size();
		nums = arr;
		tree.resize(4*size);
		propagate.resize(4*size);
		build(0,0,size-1);
	}
	int getSum(int left, int right){
		return query(0, 0, size-1, left, right);
	}
	int getTreeSum(){ return tree[0]; }

	void addVal(int left_index, int right_index, int val){
		 update(left_index, right_index, val, 0, 0, size-1);
	}
};

int main()
{
	vector<int> arr = {1,2,3,1,1,4,5,6,2,3};
	SegmentTree* tree = new SegmentTree(arr);
	cout<<tree->getSum(0,2)<<endl;
	tree->addVal(0,2, 2);
	cout<<tree->getSum(0,2)<<endl;
	delete tree;	
	return 0;
}