// distinct substring count
class DSC {
  
  private:
  
  vector<int> LCP(const string& s, const vector<int>& sa) {
    int n = (int)s.size(), k = 0;
    vector<int> lcp(n), rank(n);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    for (int i = 0; i < n; i++, k ? k-- : 0) {
      if (rank[i] == n - 1) {
        k = 0;
        continue;
      }
      int j = sa[rank[i] + 1];
      while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
      lcp[rank[i]] = k;
    }
    lcp[n - 1] = 0;
    return lcp;
  }
  
  SuffixArray sa;
  int ans;
  
  public:
  
  DSC() {}
  DSC(
    const string &str, 
    const char first = 'a',
    const char last = 'z'
  ) {
    sa = SuffixArray(str, first, last);
    vector<int> lcp = LCP(str, sa.get());
    int n = sz(str);
    ans = n * (n + 1) / 2 - sum(lcp);
  }
  
  int get() {return ans;}
};
