// Range Sum - Point Update - 0 indexed
#include <vector>
#include <algorithm>

class SegmentTree {
private:
    int n; // Size of the input array
    std::vector<int> tree; // Stores the segment tree

    // Build the tree recursively
    void build(const std::vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start]; // Leaf node (single element)
        } else {
            int mid = (start + end) / 2;
            build(arr, 2*node + 1, start, mid);    // Build left child
            build(arr, 2*node + 2, mid + 1, end);  // Build right child
            tree[node] = tree[2*node + 1] + tree[2*node + 2]; // Merge children
        }
    }

    // Point Update - Add/Replace
    void pointUpdate(int node, int start, int end, int idx, int value, bool isReplace=true) {
        if (start == end) {
            if (isReplace)
                tree[node] = value;  // Replace the value
            else
                tree[node] += value; // Add to the existing value
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                pointUpdate(2 * node + 1, start, mid, idx, value, isReplace); // Left subtree
            } else {
                pointUpdate(2 * node + 2, mid + 1, end, idx, value, isReplace); // Right subtree
            }
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2]; // Recalculate sum
        }
    }


    // Query sum in range [l, r]
    int queryRange(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0; // No overlap
        if (l <= start && end <= r) return tree[node]; // Complete overlap
        int mid = (start + end) / 2;
        // Partial overlap: query both children
        return queryRange(2*node + 1, start, mid, l, r) + 
               queryRange(2*node + 2, mid + 1, end, l, r);
    }

public:
    SegmentTreeSum(const std::vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n, 0); // Allocate memory (4*n is safe size)
        build(arr, 0, 0, n - 1); // Build from root node (index 0)
    }

    // Public method to update value at index `idx`
    void update(int idx, int value) {
        pointUpdate(0, 0, n - 1, idx, value);
    }

    // Public method to get sum in range [l, r]
    int get(int l, int r) {
        return queryRange(0, 0, n - 1, l, r);
    }
};

// Example usage
int main() {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTreeSum st(arr);

    std::cout << "Sum in range [1, 3]: " << st.get(1, 3) << std::endl; // Output: 15 (3+5+7)

    st.update(2, 7); // Change element at index 2 from 5 → 7
    std::cout << "Sum in range [1, 3] after update: " << st.get(1, 3) << std::endl; // Output: 17 (3+7+7)

    return 0;
}

// =============================================================================================================

// RangeSum - Point Update
struct SegTree {
public:
 
    SegTree (int _n) : n (_n) {
        tree.resize(4*n, 0);
    }
    
    int query (int x, int y) {
        return query (x, y, 0, n-1, 0);
    }
    
    void update (int ind, int val) {
        update (ind, val, 0, n-1, 0);
    }
 
private:
    
    vector<int> tree;
    int n;
    
    int query (int x, int y, int l, int r, int i) {
        if (r < x || l > y) return 0;
        if (l >= x && r <= y) return tree[i];
        
        int m = (l+r) >> 1;
        return (
            query (x, y, l, m, i*2+1) +
            query (x, y, m+1, r, i*2+2)
        );
    }
    
    void update (int ind, int val, int l, int r, int i) {
        if (l == r) {
            tree[i] += val;
            return;
        }
        
        int m = (l+r) >> 1;
        if (m >= ind) update (ind, val, l, m, i*2+1);
        else update (ind, val, m+1, r, i*2+2);
        
        tree[i] = tree[i*2+1] + tree[i*2+2];
    }
};

// Merge Sort Segment Tree
struct SegmentTree {
public:
    SegmentTree (int _n, const vector<int>& arr) : n (_n) {
        tree.resize(4*n);
        build (0, n-1, 0, arr);
    }
 
    int query (int x, int y, int k) {
        return query (x, y, k, 0, n-1, 0);
    }
 
private:
    void build (int l, int r, int i, const vector<int>& arr) {
        if (l == r) {
            tree[i] = {arr[l]};
            return;
        }
 
        int m = (l+r) >> 1;
        build (l, m, i*2+1, arr);
        build (m+1, r, i*2+2, arr);
 
        tree[i] = Merge (tree[i*2+1], tree[i*2+2]);
    }
 
    vector<int> Merge (const vector<int>& lft, const vector<int>& rgt) {
        vector<int> result;
        int n1 = lft.size(), n2 = rgt.size();
        int l1 = 0, l2 = 0;
 
        while (l1 < n1 && l2 < n2) {
            if (lft[l1] <= rgt[l2]) {
                result.push_back(lft[l1]);
                l1 ++;
            }
            else {
                result.push_back(rgt[l2]);
                l2 ++;
            }
        }
        while (l1 < n1) result.push_back(lft[l1 ++]);
        while (l2 < n2) result.push_back(rgt[l2 ++]);
 
        return result;
    }

    // (finding # of elements greater than k in the range x to y)
    int query (int x, int y, int k, int l, int r, int i) {
        if (r < x || l > y) return 0;
        if (l >= x && r <= y) {
            // change this 
            int ind = upper_bound(tree[i].begin(), tree[i].end(), k) - tree[i].begin();
            return (tree[i].size() - ind);
        }
 
        int m = (l+r) >> 1;
        return (
            query (x, y, k, l, m, i*2+1) + 
            query (x, y, k, m+1, r, i*2+2)
        );
    }
 
    vector<vector<int>> tree;
    int n;
};

// Persistant trees

struct SegmentTree {
 
public:
    SegmentTree (int _n) : n(_n) {
        roots.push_back(BuildInitialTree(0, n-1));
    }
 
    void UpdateValue (int ind, int val) {
        roots.push_back(BuildNewVersion(roots.back(), ind, val, 0, n-1));
    }
 
    int Query (int ind, int x, int y) {
        return query (x, y, roots[ind], 0, n-1);
    }
 
private:
    struct Node {
        int val;
        Node *lft, *rgt;
 
        Node(int _val) : val(_val), lft(NULL), rgt(NULL) {} 
    };
 
    Node* BuildInitialTree (int l, int r) {
        if (l == r) return new Node(0);
 
        Node* result = new Node(0);
        int m = (l+r) >> 1;
        result -> lft = BuildInitialTree(l, m);
        result -> rgt = BuildInitialTree(m+1, r);
 
        return result;
    }
 
    Node* BuildNewVersion (Node* prv_root, int ind, int val, int l, int r) {
        if (l == r) return new Node(val);
 
        Node* ans = new Node(0);
        int m = (l+r) >> 1;
        if (m >= ind) {
            ans -> lft = BuildNewVersion(prv_root -> lft, ind, val, l, m);
            ans -> rgt = prv_root -> rgt;
        }
        else {
            ans -> lft = prv_root -> lft;
            ans -> rgt = BuildNewVersion(prv_root -> rgt, ind, val, m+1, r);
        }
 
        ans -> val = ans -> lft -> val + ans -> rgt -> val;
        return ans;
    }
 
    int query (int x, int y, Node* root, int l, int r) {
        if (r < x || l > y) return 0;
        if (l >= x && r <= y) return root -> val;
 
        int m = (l+r) >> 1;
        return (
            query(x, y, root->lft, l, m) + 
            query(x, y, root->rgt, m+1, r)
        );
    }
 
    vector<Node*> roots;
    int n;
};
