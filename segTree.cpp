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
