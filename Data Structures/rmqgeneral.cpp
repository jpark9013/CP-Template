template<typename T> class RMQ {
  
  using ftype = function<T(T, T)>;
  
  public:
  
  RMQ() {}
  
  RMQ(vector<T> arr, const T &val, const ftype &_f) : f(_f), identity(val) {
    int pow2 = 1, cnt = 0;
    for (; pow2 < arr.size(); pow2 *= 2, ++cnt);
    
    arr.resize(pow2, identity);
    sum.resize(cnt, vector<T>(pow2));
    
    for(int level = 0; level < sum.size(); ++level) {
      for(int block = 0; block < 1 << level; ++block) {
        const auto start = block << (sum.size() - level);
        const auto end = (block + 1) << (sum.size() - level);
        const auto middle = (end + start) / 2;
        
        auto val = arr[middle];
        sum[level][middle] = val;
        for(int x = middle + 1; x < end; ++x) {
          val = f(val, arr[x]);
          sum[level][x] = val;
        }
        
        val = arr[middle - 1];
        sum[level][middle - 1] = val;
        for(int x = middle-2; x >= start; --x) {
          val = f(val, arr[x]);
          sum[level][x] = val;
        }
      }
    }
  }
  
  T get(int l, int r) const {
    assert(l <= r);
    if(r == l-1){
      return identity;
    }
    if(l == r){
      return sum.back()[l];
    }
    const auto pos_diff = (sizeof(int64_t) * CHAR_BIT) - 1 - __builtin_clzll(l ^ r);
    const auto level = sum.size() - 1 - pos_diff;
    return f(sum[level][l], sum[level][r]);
  }
  
  private:
  
  vector<vector<T>> sum;
  ftype f;
  T identity;
};
