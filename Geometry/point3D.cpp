struct Point {
  long double x, y, z;

  Point() : x(0), y(0), z(0) {}
  Point(long double x, long double y, long double z) : x(x), y(y), z(z) {}

  Point operator - (Point b) {
    return Point(x - b.x, y - b.y, z - b.z);
  }
  Point operator + (Point b) {
    return Point(x + b.x, y + b.y, z + b.z);
  }
  Point operator * (long double k) {
    return Point(x * k, y * k, z * k);
  }
  Point operator / (long double k) {
    return Point(x / k, y / k, z / k);
  }

  long double len() {
    return sqrt(x * x + y * y + z * z);
  }

  long double dp(Point b) {
    return x * b.x + y * b.y + z * b.z;
  }

  Point cp(Point b) {
    return Point(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
  }
};
long double tp(Point a, Point b, Point c) {
  return a.dp(b.cp(c));
}
string to_string(Point a) {
  return "(" + to_string(a.x) + ", " + to_string(a.y) + ", " + to_string(a.z) + ")";
}
ostream& operator << (ostream& o, const Point &p) {
  return o << to_string(p);
}
struct Tr {
  Point a, b, c;
  Point norm;

  Tr() {}
  Tr(Point _a, Point _b, Point _c, Point _norm = Point(0, 0, 0)) : a(_a), b(_b), c(_c), norm(_norm) {
    // if (a.i > b.i)
    //   swap(a, b);
    // if (a.i > c.i)
    //   swap(a, c);
    // if (b.i > c.i)
    //   swap(b, c);
  }
};
