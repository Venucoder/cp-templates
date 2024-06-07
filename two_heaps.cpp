class MedianMaintainer {
private:
    // Max-heap for the left half
    std::priority_queue<int> maxHeap;
    
    // Min-heap for the right half
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    
public:
    // Insert a new value
    void insert(int value) {
        if (maxHeap.empty() || value <= maxHeap.top()) {
            maxHeap.push(value);
        } else {
            minHeap.push(value);
        }
        
        // Balance the heaps
        if (maxHeap.size() > minHeap.size() + 1) {
            int top = maxHeap.top();
            minHeap.push(top);
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            int top = minHeap.top();
            maxHeap.push(top);
            minHeap.pop();
        }
    }
    
    // Get the median value
    int getMedian() const {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        } else {
            return (maxHeap.top() + minHeap.top()) / 2;
        }
    }
    
    // Get the size of the maxHeap
    int getMaxHeapSize() const {
        return maxHeap.size();
    }
    
    // Get the size of the minHeap
    int getMinHeapSize() const {
        return minHeap.size();
    }
};

// To use
int main() {
  MedianMaintainer mm;
}
