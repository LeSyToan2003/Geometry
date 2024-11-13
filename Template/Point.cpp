struct Point {
    typedef int T; T x, y;
    Point() {} Point(T _x, T _y) { x = _x, y = _y; }
    bool operator == (Point p) { return x == p.x && y == p.y; }
    bool operator < (Point p) { return pos() != p.pos() ? pos() < p.pos() : cross(p) > 0; }
    bool pos() { return y > 0 || (y == 0 && x < 0); }
    Point rotating(T a) { return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
    Point rotating(Point p, T a) { return (*this - p).rotating(a) + p; }
    T dot(Point p) { return x * p.x + y * p.y; }
    T cross(Point p) { return x * p.y - y * p.x; }
    T area(Point pa, Point pb) { return abs((pa - *this).cross(pb - *this)); }
    T dist_line(Point pa, Point pb) { return area(pa, pb) / (pa - pb).norm(); }
    T dist_seg(Point pa, Point pb) {
        T a = (pa - *this).norm(), b = (pb - *this).norm(), c = (pa - pb).norm();
        if (a * a + c * c < b * b) return a;
        if (b * b + c * c < a * a) return b;
        return area(pa, pb) / c;
    }
    T ccw(Point pa, Point pb) {
        T c = (pa - *this).cross(pb - *this);
        return c == 0 ? 0 : (c > 0 ? 1 : - 1);
    }
    bool on(Point pa, Point pb) { return ccw(pa, pb) == 0 && (pa - *this).dot(pb - *this) <= 0; }
    Point proj(Point pa, Point pb) {
        T a = (pa - *this).norm(), b = (pb - *this).norm(), c = (pa - pb).norm();
        T h = area(pa, pb) / c, d = sqrt(a * a - h * h);
        if (a * a + c * c < b * b) return (pa - pb) * (d + c) / c + pb;
        return (pb - pa) * d / c + pa;
    }
    Point ref(Point pa, Point pb) { return proj(pa, pb) * 2 - *this; }
    bool in_SP(vector <Point> &vecP) {
        int n = vecP.size(), cnt = 0;
        for (int i = 0; i < n; ++i) {
            Point pa = vecP[i], pb = vecP[(i + 1) % n];
            if (on(pa, pb)) return true;
            if (pa.y > pb.y) swap(pa, pb);
            if (pa.y <= y && y < pb.y && ccw(pa, pb) < 0) cnt++;
        }
        return cnt % 2 == 1;
    }
    bool in_CP(vector <Point> &vecP) {
        int n = vecP.size(), l = 2, r = n - 1;
        if (on(vecP[0], vecP[1]) || on(vecP[0], vecP[n - 1])) return true;
        while (l < r) {
            int m = (l + r) / 2;
            if (ccw(vecP[0], vecP[m]) <= 0) r = m;
            else l = m + 1;
        }
        if (on(vecP[r], vecP[r - 1])) return true;
        vector <Point> vecTri = {vecP[0], vecP[r - 1], vecP[r]};
        return in_SP(vecTri);
    }
};