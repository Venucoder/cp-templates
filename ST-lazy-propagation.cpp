// Sum with Lazy Prop can be used for (Min, Max, GCD)
#include <vector>
#include <algorithm>
#include <climits>

class SegmentTree {
private:
    int n; // Size of the input array
    std::vector<int> tree; // Segment Tree
    std::vector<int> lazy; // Lazy propagation array

    // Function to build the tree
    void build(const std::vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start]; // Leaf node
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node + 1, start, mid); // Left child
            build(arr, 2 * node + 2, mid + 1, end); // Right child
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2]; // Merge operation
        }
    }

    // Function to propagate lazy values
    void propagate(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node]; // Apply lazy value
            if (start != end) { // Not a leaf node
                lazy[2 * node + 1] += lazy[node]; // Propagate to left child
                lazy[2 * node + 2] += lazy[node]; // Propagate to right child
            }
            lazy[node] = 0; // Reset lazy value
        }
    }

    // Function to perform a range update
    void rangeUpdate(int node, int start, int end, int l, int r, int val) {
        propagate(node, start, end); // Propagate lazy values
        if (start > r || end < l) return; // No overlap
        if (l <= start && end <= r) { // Complete overlap
            tree[node] += (end - start + 1) * val; // Update current node
            if (start != end) { // Not a leaf node
                lazy[2 * node + 1] += val; // Mark left child as lazy
                lazy[2 * node + 2] += val; // Mark right child as lazy
            }
            return;
        }
        int mid = (start + end) / 2;
        rangeUpdate(2 * node + 1, start, mid, l, r, val); // Update left child
        rangeUpdate(2 * node + 2, mid + 1, end, l, r, val); // Update right child
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2]; // Merge operation
    }

    // Function to query a range
    int query(int node, int start, int end, int l, int r) {
        propagate(node, start, end); // Propagate lazy values
        if (start > r || end < l) return 0; // No overlap
        if (l <= start && end <= r) return tree[node]; // Complete overlap
        int mid = (start + end) / 2;
        int left = query(2 * node + 1, start, mid, l, r); // Query left child
        int right = query(2 * node + 2, mid + 1, end, l, r); // Query right child
        return left + right; // Merge operation
    }

public:
    // Constructor
    SegmentTree(const std::vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n, 0); // Initialize tree
        lazy.resize(4 * n, 0); // Initialize lazy array
        build(arr, 0, 0, n - 1); // Build the tree
    }

    // Range update
    void update(int l, int r, int val) {
        rangeUpdate(0, 0, n - 1, l, r, val);
    }

    // Range query
    int get(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};

// Example usage
int main() {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree st(arr);

    std::cout << "Sum in range [1, 3]: " << st.get(1, 3) << std::endl; // Output: 15

    st.update(1, 3, 2); // Add 2 to elements in range [1, 3]
    std::cout << "Sum in range [1, 3] after update: " << st.get(1, 3) << std::endl; // Output: 21

    return 0;
}

/*=====================================================================================================================*/




#include<bits/stdc++.h>
using namespace std; 
class ST {
	vector<int> seg, lazy; 
public: 
	ST(int n) {
		seg.resize(4 * n); 
		lazy.resize(4 * n); 
	}
public: 
	void build(int ind, int low, int high, int arr[]) {
		if(low == high) {
			seg[ind] = arr[low];
			return; 
		}
		int mid = (low + high) >> 1; 
		build(2*ind+1, low, mid, arr); 
		build(2*ind+2, mid+1, high, arr); 
		seg[ind] = seg[2*ind+1] + seg[2*ind+2];
	}
public:
	void update(int ind, int low, int high, int l, int r, 
		int val) {
		// update the previous remaining updates 
		// and propogate downwards 
		if(lazy[ind] != 0) {
			seg[ind] += (high - low + 1) * lazy[ind]; 
			// propogate the lazy update downwards
			// for the remaining nodes to get updated 
			if(low != high) {
				lazy[2*ind+1] += lazy[ind]; 
				lazy[2*ind+2] += lazy[ind]; 
			}

			lazy[ind] = 0; 
		}

		// no overlap 
		// we don't do anything and return 
		// low high l r or l r low high 
		if(high < l or r < low) {
			return; 
		}

		// complete overlap 
		// l low high r 
		if(low>=l && high <= r) {
			seg[ind] += (high - low + 1) * val; 
			// if a leaf node, it will have childrens
			if(low != high) {
				lazy[2*ind+1] += val; 
				lazy[2*ind+2] += val; 
			}
			return; 
		}
		// last case has to be no overlap case
		int mid = (low + high) >> 1; 
		update(2*ind+1, low, mid, l, r, val);
		update(2*ind+2, mid+1, high, l, r, val); 
		seg[ind] = seg[2*ind+1] + seg[2*ind+2]; 
	}
public: 
	int query(int ind, int low, int high, int l, int r) {

		// update if any updates are remaining 
		// as the node will stay fresh and updated 
		if(lazy[ind] != 0) {
			seg[ind] += (high - low + 1) * lazy[ind]; 
			// propogate the lazy update downwards
			// for the remaining nodes to get updated 
			if(low != high) {
				lazy[2*ind+1] += lazy[ind]; 
				lazy[2*ind+2] += lazy[ind]; 
			}

			lazy[ind] = 0; 
		}

		// no overlap return 0; 
		if(high < l or r < low) {
			return 0; 
		}

		// complete overlap 
		if(low>=l && high <= r) return seg[ind]; 

		int mid = (low + high) >> 1; 
		int left = query(2*ind+1, low, mid, l, r);
		int right = query(2*ind+2, mid+1, high, l, r);
		return left + right; 
	}
};


class STMin {
	vector<int> seg, lazy; 
public: 
	STMin(int n) {
		seg.resize(4 * n); 
		lazy.resize(4 * n); 
	}
public: 
	void build(int ind, int low, int high, int arr[]) {
		if(low == high) {
			seg[ind] = arr[low];
			return; 
		}
		int mid = (low + high) >> 1; 
		build(2*ind+1, low, mid, arr); 
		build(2*ind+2, mid+1, high, arr); 
		seg[ind] = min(seg[2*ind+1], seg[2*ind+2]);
	}
public:
	void update(int ind, int low, int high, int l, int r, 
		int val) {
		// update the previous remaining updates 
		// and propogate downwards 
		if(lazy[ind] != 0) {
			seg[ind] += lazy[ind]; 
			// propogate the lazy update downwards
			// for the remaining nodes to get updated 
			if(low != high) {
				lazy[2*ind+1] += lazy[ind]; 
				lazy[2*ind+2] += lazy[ind]; 
			}

			lazy[ind] = 0; 
		}

		// no overlap 
		// we don't do anything and return 
		// low high l r or l r low high 
		if(high < l or r < low) {
			return; 
		}

		// complete overlap 
		// l low high r 
		if(low>=l && high <= r) {
			seg[ind] += val; 
			// if a leaf node, it will have childrens
			if(low != high) {
				lazy[2*ind+1] += val; 
				lazy[2*ind+2] += val; 
			}
			return; 
		}
		// last case has to be no overlap case
		int mid = (low + high) >> 1; 
		update(2*ind+1, low, mid, l, r, val);
		update(2*ind+2, mid+1, high, l, r, val); 
		seg[ind] = min(seg[2*ind+1], seg[2*ind+2]); 
	}
public: 
	int query(int ind, int low, int high, int l, int r) {

		// update if any updates are remaining 
		// as the node will stay fresh and updated 
		if(lazy[ind] != 0) {
			seg[ind] += lazy[ind]; 
			// propogate the lazy update downwards
			// for the remaining nodes to get updated 
			if(low != high) {
				lazy[2*ind+1] += lazy[ind]; 
				lazy[2*ind+2] += lazy[ind]; 
			}

			lazy[ind] = 0; 
		}

		// no overlap return 0; 
		if(high < l or r < low) {
			return INT_MAX; 
		}

		// complete overlap 
		if(low>=l && high <= r) return seg[ind]; 

		int mid = (low + high) >> 1; 
		int left = query(2*ind+1, low, mid, l, r);
		int right = query(2*ind+2, mid+1, high, l, r);
		return min(left,right); 
	}
};


class ST {
	vector<int> seg, lazy; 
public: 
	ST(int n) {
		seg.resize(4 * n); 
		lazy.resize(4 * n); 
	}
public: 
	void build(int ind, int low, int high, int arr[]) {
		if(low == high) {
			seg[ind] = arr[low];
			return; 
		}
		int mid = (low + high) >> 1; 
		build(2*ind+1, low, mid, arr); 
		build(2*ind+2, mid+1, high, arr); 
		seg[ind] = seg[2*ind+1] + seg[2*ind+2];
	}
public:
	void update(int ind, int low, int high, int l, int r, 
		int val) {
		// update the previous remaining updates 
		// and propogate downwards 
		if(lazy[ind] != 0) {
			seg[ind] = (high - low + 1) - seg[ind]; 
			// propogate the lazy update downwards
			// for the remaining nodes to get updated 
			if(low != high) {
				lazy[2*ind+1] = !lazy[2*ind + 1]; 
				lazy[2*ind+2] = !lazy[2*ind + 2]; 
			}

			lazy[ind] = 0; 
		}

		// no overlap 
		// we don't do anything and return 
		// low high l r or l r low high 
		if(high < l or r < low) {
			return; 
		}

		// complete overlap 
		// l low high r 
		if(low>=l && high <= r) {
			seg[ind] = (high - low + 1) - val; 
			// if a leaf node, it will have childrens
			if(low != high) {
				lazy[2*ind+1] = !lazy[2*ind + 1]; 
				lazy[2*ind+2] = !lazy[2*ind + 2]; 
			}
			return; 
		}
		// last case has to be no overlap case
		int mid = (low + high) >> 1; 
		update(2*ind+1, low, mid, l, r, val);
		update(2*ind+2, mid+1, high, l, r, val); 
		seg[ind] = seg[2*ind+1] + seg[2*ind+2]; 
	}
public: 
	int query(int ind, int low, int high, int l, int r) {

		// update if any updates are remaining 
		// as the node will stay fresh and updated 
		if(lazy[ind] != 0) {
			seg[ind] = (high - low + 1) - seg[ind]; 
			// propogate the lazy update downwards
			// for the remaining nodes to get updated 
			if(low != high) {
				lazy[2*ind+1] = !lazy[2*ind + 1]; 
				lazy[2*ind+2] = !lazy[2*ind + 2]; 
			}

			lazy[ind] = 0; 
		}

		// no overlap return 0; 
		if(high < l or r < low) {
			return 0; 
		}

		// complete overlap 
		if(low>=l && high <= r) return seg[ind]; 

		int mid = (low + high) >> 1; 
		int left = query(2*ind+1, low, mid, l, r);
		int right = query(2*ind+2, mid+1, high, l, r);
		return left + right; 
	}
};
int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin); 
	freopen("output.txt", "w", stdout); 
	#endif
	int n;
	cin >> n; 
	int arr[n];
	for(int i = 0;i<n;i++) cin >> arr[i]; 
	ST st(n+1); 
	st.build(0,0,n-1, arr); 

	int q;
	cin >> q; 
	while(q--) {
		int type;
		cin >> type; 
		if(type==1) {
			int l, r;
			cin >> l >> r;
			cout << st.query(0,0,n-1,l,r) << endl; 
		}
		else {
			int l, r, val;
			cin >> l >> r >> val; 
			st.update(0,0,n-1,l,r,val);
		}
	}
	return 0; 
}
