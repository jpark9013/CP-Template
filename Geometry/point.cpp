struct Point {
  ld x, y;

  Point(ld x = 0, ld y = 0): x(x), y(y) {}
  Point(Point a, Point b) {
    x = b.x - a.x;
    y = b.y - a.y;
  }

  ld dist(Point b) const {
    return sqrt((b.x - x) * (b.x - x) + (b.y - y) * (b.y - y));
  }
  ld sdist(Point b) const {
    return ((b.x - x) * (b.x - x) + (b.y - y) * (b.y - y));
  }
  ld len() const {
    return sqrt(x * x + y * y);
  }
  ld slen() const {
    return x * x + y * y;
  }
  Point ort() const {
    return Point(-y, x);
  }
  ld dp(Point p) const {
    return x * p.x + y * p.y;
  }
  ld cp(Point p) const {
    return x * p.y - y * p.x;
  }

  Point operator + (Point a) const {
    return Point(a.x + x, a.y + y);
  }
  Point operator - (Point a) const {
    return Point(x - a.x, y - a.y);
  }
  Point operator * (ld k) const {
    return Point(x * k, y * k);
  }
  Point operator / (ld k) const {
    return Point(x / k, y / k);
  }

  Point& norm() {
    ld d = len();
    if (d != 0) {
      x /= d;
      y /= d;
    }
    return *this;
  }
};
ostream& operator << (ostream& o, const Point &p) {
  return o << "(" << p.x << ", " << p.y << ")";
}
