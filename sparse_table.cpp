template<typename T>
T combine(T a, T b) {
    return min(a, b); 
}
template<typename T>
struct SparseTable {
    int n;
    vector<vector<T>> st;
    vector<int> log_table;

    SparseTable(const vector<T>& arr) : n(arr.size()) {
        log_table.resize(n + 1);
        for (int i = 2; i <= n; i++) {
            log_table[i] = log_table[i/2] + 1;
        }

        int k = log_table[n] + 1;
        st.resize(k, vector<T>(n));
        st[0] = arr;

        for (int j = 1; j < k; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = combine(st[j-1][i], st[j-1][i + (1 << (j-1))]);
            }
        }
    }

    T query(int L, int R) {
        int j = log_table[R - L + 1];
        return combine(st[j][L], st[j][R - (1 << j) + 1]);
    }
};

SparseTable<int> st(a);
