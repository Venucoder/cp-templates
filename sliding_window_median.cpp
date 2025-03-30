class SWM {
public:
    void rebalance(multiset<long long, greater<long long>> &maxHeap, multiset<long long> &minHeap) {
        if(!maxHeap.empty() and !minHeap.empty() and *maxHeap.begin() > *minHeap.begin()) {
            minHeap.insert(*maxHeap.begin());
            maxHeap.erase(maxHeap.begin());
        }
        if(maxHeap.size() > minHeap.size() + 1) {
            minHeap.insert(*maxHeap.begin());
            maxHeap.erase(maxHeap.begin());
        }
        if(minHeap.size() > maxHeap.size() + 1) {
            maxHeap.insert(*minHeap.begin());
            minHeap.erase(minHeap.begin());
        }
    }
    
    void addEle(multiset<long long, greater<long long>> &maxHeap, multiset<long long> &minHeap, int val) {
        maxHeap.insert(val);
        rebalance(maxHeap, minHeap);
    }

    void removeEle(multiset<long long, greater<long long>> &maxHeap, multiset<long long> &minHeap, int val) {
        if (maxHeap.find(val) != maxHeap.end())
            maxHeap.erase(maxHeap.find(val));
        else
            minHeap.erase(minHeap.find(val));
        rebalance(maxHeap, minHeap);
    }

    double findMedian(multiset<long long, greater<long long>> &maxHeap, multiset<long long> &minHeap) {
        if(maxHeap.size() > minHeap.size()) {
            return *maxHeap.begin();
        }
        if(minHeap.size() > maxHeap.size()) {
            return *minHeap.begin();
        }
        return (double)(*maxHeap.begin() + *minHeap.begin()) / 2;
    }

    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        multiset<long long, greater<long long>> maxHeap; // smaller
        multiset<long long> minHeap; // larger            
        int n = nums.size();
        vector<double> res;
        for(int i = 0; i < n; i++) {
            if(i >= k) {
                removeEle(maxHeap, minHeap, nums[i-k]);
            }
            addEle(maxHeap, minHeap, nums[i]);
            if(i >= k-1) {
                res.push_back(findMedian(maxHeap, minHeap));
            }
        }
        return res;
    }
};

SWM swm;
swm.medianSlidingWindow(nums, k);
