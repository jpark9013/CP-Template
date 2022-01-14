template<typename T> struct sliding {
  vector<T> frontv, backv;
  vector<T> frontmx, backmx;
  
  typedef function<T(T, T)> ftype;
  ftype f;
  T val;
  bool s = 0;
  
  sliding(const T &x, const ftype &_f) : f(_f), val(x), s(1) {}
  sliding() {}
  
  void push(const T &v) {
    frontv.push_back(v);
    if (frontmx.size()) frontmx.push_back(f(frontmx.back(), v)); 
    else frontmx.push_back(v);
  }
  
  void pop() {
    if (!backv.size()) {
      while (frontv.size()) {
        backv.push_back(frontv.back());
        if (backmx.size()) backmx.push_back(f(backmx.back(), frontv.back())); 
        else backmx.push_back(frontv.back());
        frontv.pop_back();
      }
      frontmx.clear();
    }
    if (backv.empty()) return; 
    backmx.pop_back();
    backv.pop_back();
  }
  
  T get() {
    if (frontmx.size() && backmx.size()) return f(frontmx.back(), backmx.back());
    if (frontmx.size()) return frontmx.back();
    if (backmx.size()) return backmx.back();
    assert(s);
    return val;
  }
};
