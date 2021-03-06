struct item {
  template<typename T>
  void init(const T &t, int l, int r) {
  }

  void update(const item &first, const item &second, int l, int r) {
  }

  static item merge(const item &first, const item &second, int l, int r) {
    item res;
    res.update(first, second, l, r);  // careful with different lengths
    return res;
  }

  template<typename Modifier>
  void modify(const Modifier &m, int l, int r) {
    // apply here, save for children
  }

  void push(item &first, item &second, int l, int r) {
    // int m = (l + r) / 2;
    // first.modify(, l, m);
    // second.modify(, m + 1, r);
    // reset modifier
  }
};

string to_string(const item &i) {
  stringstream ss;
  ss << "[" << "]";
  return ss.str();
}
ostream& operator << (ostream &o, const item &i) {
  return o << to_string(i);
}

struct SegTree {
  
  private:
  
  vector<item> tree;
  int n = 1;
  
  void check(int l, int r) {
    assert(l >= 0 && l <= r && r <= n - 1);
  }

  template<typename T>
  void build(const vector<T> &v, int i, int l, int r) {
    if (l == r) {
      tree[i].init(v[l], l, r);
      return;
    }
    int m = (l + r) >> 1;
    build(v, i * 2 + 1, l, m);
    build(v, i * 2 + 2, m + 1, r);
    tree[i].update(tree[i * 2 + 1], tree[i * 2 + 2], l, r);
  }

  template<typename T>
  void build(const vector<T> &v) {
    n = v.size();
    tree.resize(1 << (__lg(MAX(1, n - 1)) + 2));
    build(v, 0, 0, n - 1);
  }

  item ask(int l, int r, int i, int vl, int vr) {
    if (vl != vr) {
      tree[i].push(tree[i * 2 + 1], tree[i * 2 + 2], vl, vr);
    }
    if (l == vl && r == vr) {
      return tree[i];
    }
    int m = (vl + vr) >> 1;
    if (r <= m) {
      return ask(l, r, i * 2 + 1, vl, m);
    } else if (m < l) {
      return ask(l, r, i * 2 + 2, m + 1, vr);
    } else {
      return item::merge(ask(l, m, i * 2 + 1, vl, m), ask(m + 1, r, i * 2 + 2, m + 1, vr), l, r);
    }
  }

  template<typename Modifier>
  void modify(int l, int r, const Modifier &modifier, int i, int vl, int vr) {
    if (vl != vr) {
      tree[i].push(tree[i * 2 + 1], tree[i * 2 + 2], vl, vr);
    }
    if (l == vl && r == vr) {
      tree[i].modify(modifier, vl, vr);
      return;
    }
    int m = (vl + vr) >> 1;
    if (r <= m) {
      modify(l, r, modifier, i * 2 + 1, vl, m);
    } else if (m < l) {
      modify(l, r, modifier, i * 2 + 2, m + 1, vr);
    } else {
      modify(l, m, modifier, i * 2 + 1, vl, m);
      modify(m + 1, r, modifier, i * 2 + 2, m + 1, vr);
    }
    tree[i].update(tree[i * 2 + 1], tree[i * 2 + 2], vl, vr);
  }
  
  public:
  
  template<typename T>
  void update(int ind, const T &t) {
    static array<pair<int, int>, 30> st;
    int l = 0, r = n - 1, i = 0;
    int ptr = -1;
    while (l != r) {
      if (l != r) {
        tree[i].push(tree[i * 2 + 1], tree[i * 2 + 2], l, r);
      }
      st[++ptr] = {l, r};
      int m = (l + r) >> 1;
      if (ind <= m) {
        i = i * 2 + 1;
        r = m;
      } else {
        i = i * 2 + 2;
        l = m + 1;
      }
    }
    tree[i].init(t, l, r);
    while (i != 0) {
      i = (i - 1) / 2;
      tree[i].update(tree[i * 2 + 1], tree[i * 2 + 2], st[ptr].first, st[ptr].second);
      --ptr;
    }
  }
  
  item get(int l, int r) {
    check(l, r);
    if (l > r) return item();
    return ask(l, r, 0, 0, n - 1);
  }
  
  template<typename Modifier>
  void add(int l, int r, const Modifier &modifier) {
    check(l, r);
    modify(l, r, modifier, 0, 0, n - 1);
  }
  
  SegTree() {}
  template<typename T> SegTree(const vector<T> &vec) {build(vec);}
};
