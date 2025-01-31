// DSU by size
class DSU {
private:
    vector<int> parent; // Stores the parent of each element
    vector<int> size;   // Stores the size of each set

public:
    // Constructor to initialize DSU with 'n' elements
    DSU(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1); // Initially, each set has size 1
        for (int i = 1; i <= n; ++i) {
            parent[i] = i; // Each element is its own parent initially
        }
    }

    // Find the root of the set containing 'x' with path compression
    int find(int x) {
        if (parent[x] == x) return x; // If x is the root, return x
        return parent[x] = find(parent[x]); // Path compression: set parent[x] to root
    }

    // Union two sets containing 'x' and 'y' by size
    void unite(int x, int y) {
        int rootX = find(x); // Find root of x
        int rootY = find(y); // Find root of y
        if (rootX == rootY) return; // Already in the same set

        // Union by size: attach smaller set to larger set
        if (size[rootX] < size[rootY]) {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        } else {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }

    // Check if 'x' and 'y' are in the same set
    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    // Get the size of the set containing 'x'
    int getSize(int x) {
        return size[find(x)];
    }
};

// By Rank
class DSU {
private:
    vector<int> parent, rank;

public:
    DSU(int size) {
        parent.resize(size);
        rank.resize(size, 0);

        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void union_set(int x, int y) {
        int xset = find(x), yset = find(y);
        if (xset == yset) {
            return;
        } else if (rank[xset] < rank[yset]) {
            parent[xset] = yset;
        } else if (rank[xset] > rank[yset]) {
            parent[yset] = xset;
        } else {
            parent[yset] = xset;
            rank[xset]++;
        }
    }
};
DSU dsu(size);
