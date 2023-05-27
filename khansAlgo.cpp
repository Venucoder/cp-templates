vector<int> khansAlgo(vector<vector<int>> &edges, int k) {
    vector<int> indegree(k+1, 0);
    vector<int> adj[k+1];

    for(auto edge: edges) {
        indegree[edge[1]]++;
        adj[edge[0]].push_back(edge[1]);
    }

    queue<int> q;
    for(int i = 1; i <= k; i++) {
        if(indegree[i] == 0) q.push(i);
    }

    vector<int> ans;
    while(!q.empty()) {
        auto node = q.front(); q.pop();
        ans.push_back(node);
        for(auto nei: adj[node]) {
            indegree[nei]--;
            if(indegree[nei] == 0) {
                q.push(nei);
            }
        }
    }
    return ans;
}
