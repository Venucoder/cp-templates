vector<long long> subsets_of_N(int x){
  vector<long long> res;
  for(long long i=(1ll<<60)-1; i>=0; i--){
    i&=x;
    res.push_back(i);
  }
  reverse(res.begin(),res.end());
  return res;
}

