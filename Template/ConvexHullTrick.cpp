struct Line {
    typedef int T; T a, b;
    bool operator < (Line l) { return a != l.a ? a < l.a : b > l.b; }
    T getY(T x) { return a * x + b; }
};
struct CHTrick {
    typedef int T; vector <Line> vecL;
    void update(Line l) {
        while (vecL.size() > 1) {
            Line l1 = vecL[vecL.size() - 1], l2 = vecL[vecL.size() - 2];
            if (1LL * (l2.b - l.b) * (l1.a - l2.a) < 1LL * (l2.b - l1.b) * (l.a - l2.a)) 
                vecL.pop_back();
            else break;
        }
        if (vecL.empty() || l.a != vecL.back().a) vecL.push_back(l);
    }
    T query(T x) {
        int n = vecL.size(), l = 0, r = n - 2;
        if (n >= 2 && vecL[n - 2].b - vecL[n - 1].b <= x * (vecL[n - 1].a - vecL[n - 2].a)) 
            return vecL[n - 1].getY(x);
        while (l < r) {
            int m = (l + r) / 2;
            if (vecL[m].b - vecL[m + 1].b >= x * (vecL[m + 1].a - vecL[m].a)) r = m;
            else l = m + 1;
        }
        return vecL[l].getY(x);
    }
};