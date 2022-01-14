struct Line {
  long double a, b, c;
  Line() {}
  Line(long double a, long double b, long double c): a(a), b(b), c(c) {}
  Line(Point m, Point n) {
    a = n.y - m.y;
    b = m.x - n.x;
    c = -a * m.x - b * m.y;
  }
  Point intersect(Line l) {
    return Point((b * l.c - c * l.b) / (a * l.b - b * l.a), (a * l.c - c * l.a) / (b * l.a - a * l.b));
  }
  long double dist(Point p) {
    return abs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
  }
};

string to_string(Line& l) {
  string ans = "";
  if (l.a != 0) {
    ans += to_string(l.a) + "x ";
    if (l.b != 0) {
      if (l.b > 0) ans += "+";
      else ans += "-";
      ans += " " + to_string(abs(l.b)) + "y ";
    }
  }
  else ans += to_string(l.b) + "y ";
  if (l.c != 0) {
    if (l.c > 0) ans += "+";
    else ans += "-";
    ans += " " + to_string(abs(l.c)) + " ";
  }
  ans += "= 0";
  return ans;
}
ostream& operator << (ostream &o, const Line &l) {
  return o << to_string(l);
}
