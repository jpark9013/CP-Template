template <class T>
struct Matrix {
  vector<vector<T> > A;

  Matrix() = default;
  Matrix(int n, int m, T a) : A(n, vector<T>(m, a)) {}
  Matrix(int n, int m) : A(n, vector<T>(m, T())) {}
  Matrix(int n) : A(n, vector<T>(n, T())){};
  Matrix(const vector<vector<T>> &vec) : A(vec) {}

  int height() const { return A.size(); }

  int width() const { return A[0].size(); }

  int size() const { return A.size(); }

  inline const vector<T> &operator[](int k) const { return A[k]; }

  inline vector<T> &operator[](int k) { return A[k]; }

  static Matrix I(int n) {
    Matrix mat(n);
    for (int i = 0; i < n; i++) mat[i][i] = 1;
    return (mat);
  }

  Matrix &operator+=(const Matrix &B) {
    int n = height(), m = width();
    assert(n == B.H() && m == B.W());
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) (*this)[i][j] += B[i][j];
    return (*this);
  }

  Matrix &operator-=(const Matrix &B) {
    int n = height(), m = width();
    assert(n == B.H() && m == B.W());
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) (*this)[i][j] -= B[i][j];
    return (*this);
  }

  Matrix &operator*=(const Matrix &B) {
    int n = height(), m = B.width(), p = width();
    assert(p == B.height());
    vector<vector<T> > C(n, vector<T>(m, 0));
    for (int i = 0; i < n; i++)
      for (int k = 0; k < p; k++)
        for (int j = 0; j < m; j++) C[i][j] += (*this)[i][k] * B[k][j];
    A.swap(C);
    return (*this);
  }

  Matrix &operator^=(long long k) {
    Matrix B = Matrix::I(height());
    while (k > 0) {
      if (k & 1) B *= *this;
      *this *= *this;
      k >>= 1LL;
    }
    A.swap(B.A);
    return (*this);
  }

  Matrix operator+(const Matrix &B) const { return (Matrix(*this) += B); }

  Matrix operator-(const Matrix &B) const { return (Matrix(*this) -= B); }

  Matrix operator*(const Matrix &B) const { return (Matrix(*this) *= B); }

  Matrix operator^(const long long k) const { return (Matrix(*this) ^= k); }

  bool operator==(const Matrix &B) const {
    if (height() != B.height() || width() != B.width()) {
      return false;
    }
    for (int i = 0; i < height(); i++)
      for (int j = 0; j < width(); j++)
        if (A[i][j] != B[i][j]) return false;
    return true;
  }

  bool operator!=(const Matrix &B) const {
    if (height() == B.height() && width() == B.width()) return false;
    for (int i = 0; i < height(); i++)
      for (int j = 0; j < width(); j++)
        if (A[i][j] != B[i][j]) return true;
    return false;
  }

  friend ostream &operator<<(ostream &os, const Matrix &p) {
    int n = p.height(), m = p.width();
    for (int i = 0; i < n; i++) {
      os << (i ? "   " : "") << "[";
      for (int j = 0; j < m; j++) {
        os << p[i][j] << (j + 1 == m ? "]\n" : ",");
      }
    }
    return (os);
  }

  T determinant() const {
    Matrix B(*this);
    assert(height() == width());
    T ret = 1;
    for (int i = 0; i < height(); i++) {
      int idx = -1;
      for (int j = i; j < width(); j++) {
        if (B[j][i] != 0) {
          idx = j;
          break;
        }
      }
      if (idx == -1) return 0;
      if (i != idx) {
        ret *= T(-1);
        swap(B[i], B[idx]);
      }
      ret *= B[i][i];
      T inv = T(1) / B[i][i];
      for (int j = 0; j < width(); j++) {
        B[i][j] *= inv;
      }
      for (int j = i + 1; j < height(); j++) {
        T a = B[j][i];
        if (a == 0) continue;
        for (int k = i; k < width(); k++) {
          B[j][k] -= B[i][k] * a;
        }
      }
    }
    return ret;
  }
  
  Matrix inverse() {
    assert(height() == width());
    Matrix A = *this;
    int n = height();
    vector<T> col(n);
    vector<vector<T>> tmp(n,vector<T>(n));
    for (int i = 0; i < n; i++) {
      tmp[i][i] = 1;
      col[i] = i;
    }
    for (int i = 0; i < n; i++) {
      int r = i, c = i;
      for (int j = i; j < n; j++) {
        for (int k = i; k < n; k++) {
          if (A[j][k] != 0) {
            r = j;
            c = k;
            goto found;
          }
        }
      }
      
      return Matrix({});
      
      found:;
      
      A[i].swap(A[r]);
      tmp[i].swap(tmp[r]);
      for (int j =0; j < n; j++) {
        swap(A[j][i], A[j][c]);
        swap(tmp[j][i],tmp[j][c]);
      }
      swap(col[i],col[c]);
      T v = 1 / A[i][i];
      for (int j = i+1; j < n; j++) {
        T f = A[j][i]*v;
        A[j][i] = 0;
        for (int k = i+1; k < n; k++)
          A[j][k] -= f*A[i][k];
        for (int k = 0; k < n; k++)
          tmp[j][k] -= f*tmp[i][k];
      }
      for (int j = i+1; j < n; j++)
        A[i][j] *= v;
      for (int j =0; j < n; j++)
        tmp[i][j] *= v;
      A[i][i] = 1;
    }
    for (int i = n-1; i >= 0; i--) {
      for (int j = 0; j < i; j++) {
        T v = A[j][i];
        for (int k = 0; k < n; k++)
          tmp[j][k] -= v*tmp[i][k];
      }
    }
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        A[col[i]][col[j]] = tmp[i][j];
      
    return A;
  }
};
