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
