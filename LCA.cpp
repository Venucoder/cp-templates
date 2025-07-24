// LCA with Euler Tour
static constexpr int LOGN = 20; // log2(max nodes) + 1, adjust as needed
vector<vector<int>> adj;
vector<vector<int>> up;
vector<int> tin, tout, subtree_xor;
int timer = 0;

// Preprocessing DFS: fills LCA tables and computes subtree XOR
void dfs(int v, int p, const vector<int>& nums) {
    tin[v] = ++timer;
    up[v][0] = p;
    subtree_xor[v] = nums[v];
    for (int k = 1; k <= LOGN; ++k)
        up[v][k] = up[up[v][k - 1]][k - 1];
    for (int u : adj[v]) {
        if (u != p) {
            dfs(u, v, nums);
            subtree_xor[v] ^= subtree_xor[u];
        }
    }
    tout[v] = ++timer;
}

bool isAncestor(int x, int y) {
    // Returns true if x is ancestor (or equal) of y
    return tin[x] <= tin[y] && tout[x] >= tout[y];
}

int lca(int u, int v) {
    if (isAncestor(u, v)) return u;
    if (isAncestor(v, u)) return v;
    for (int k = LOGN; k >= 0; --k) {
        if (!isAncestor(up[u][k], v))
            u = up[u][k];
    }
    return up[u][0];
}

// Initialization
int n = nums.size();
adj.assign(n, {});
// Building the tree
for (const auto& edge : edges) {
    adj[edge[0]].push_back(edge[1]);
    adj[edge[1]].push_back(edge[0]);
}
up.assign(n, vector<int>(LOGN + 1));
tin.assign(n, 0);
tout.assign(n, 0);
subtree_xor.assign(n, 0);
timer = 0;

dfs(0, 0, nums); 

// Now you can access:
// subtree_xor[u]: xor of subtree rooted at u (O(1))
// lca(u, v): lowest common ancestor of any two nodes (O(logN))

// =============================================================================================================================================

int up[200005][20];
int lvl[200005];
vector<int> adj[200005];

void find_level(int src, int par, int level = 0) {
    lvl[src] = level;
    for (int child : adj[src]) {
        if (child != par)
            find_level(child, src, level + 1);
    }
}

void binary_lifting(int src, int par) {
    up[src][0] = par;
    for (int i = 1; i < 20; i++) {
        if (up[src][i - 1] != -1) 
            up[src][i] = up[up[src][i - 1]][i - 1];                
        else up[src][i] = -1;
    }

    for (int child : adj[src]) {
        if (child != par)
            binary_lifting(child, src);
    }
}

int lift_node(int node, int jump) {    
    for (int i = 19; i >= 0; i--) {
        if (node == -1 || jump == 0) break;
        if (jump >= (1 << i)) {
            jump -= (1 << i);
            node = up[node][i];
        }
    }
    return node;
}

int LCA(int u, int v) {
    if (lvl[u] < lvl[v]) 
        swap(u, v);
    u = lift_node(u, lvl[u] - lvl[v]);

    if (u == v) return u;

    for (int i = 19; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return lift_node(u, 1);
}

void solve() {   
    int n, q; cin >> n >> q;    
    for (int u = 2; u <= n; u++) {
        int v; cin >> v;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }
    
    find_level(1, 0);
    binary_lifting(1, -1);
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        cout << LCA(u, v) << endl;
    }    
}
