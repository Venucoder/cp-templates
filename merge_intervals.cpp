vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    
    vector<vector<int>> merged;
    
    for (const auto& interval : intervals) {
        // If merged is empty or no overlap with the last interval in merged
        if (merged.empty() || merged.back()[1] < interval[0]) {
            merged.push_back(interval);
        } else {
            // Overlapping intervals, merge them
            merged.back()[1] = max(merged.back()[1], interval[1]);
        }
    }
    
    return merged;
}
