// untested!
struct Point {
  ld x, y, ang, mag;
  Point(ld a, ld b) : x(a), y(b) {
    ang = atan(y/x);
    if ((x < 0 && y < 0) || (x > 0 && y < 0)) ang += pi; 
    mag = sqrt(a * a + b * b);
  }
  Point(ld a, ld b, ld c, ld d) : x(a), y(b), ang(c), mag(d) {}
  Point() {assert(false);}
  Point getr(ld a) {
    ld n = a + ang;
    return Point(cos(n)*mag, sin(n)*mag, n, mag);
  }
  // rotates this counterclockwise
  void rotate(ld a) {
    Point p = getr(a);
    *this = p;
  }
};

struct Polygon {
  vector<Point> vec;
  int s;
  auto begin() {return vec.begin();}
  auto end() {return vec.end();}
  // remember that it copies the thing!
  Polygon(const vector<Point> &v) {
    vec = v;
    s = vec.size();
  }
  Polygon() {}
  int sides() {
    return s;
  }
  ld area() {
    int l = vec.size();
    ld b = 0, c = 0;
    for (int i = 0; i < l; i++) {
      b += vec[i].x * vec[(i+1)%l].y;
      c += vec[i].y * vec[(i+1)%l].x;
    }
    return abs(b-c)/2;
  }
  Polygon getr(ld ang) {
    Polygon pg = *this;
    for (Point &p : pg) p.rotate(ang);
    return pg;
  } 
  void rotate(ld ang) {
    Polygon pg = getr(ang);
    *this = pg;
  }
};
