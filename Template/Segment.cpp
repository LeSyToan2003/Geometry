struct Segment {
    typedef double T; Point M, N;
    Segment() {} Segment(Point _M, Point _N) { M = _M, N = _N; }
    bool is_its(Segment s) {
        if (M.on(s.M, s.N) || N.on(s.M, s.N) || s.M.on(M, N) || s.N.on(M, N)) return true;
        return M.ccw(s.M, s.N) != N.ccw(s.M, s.N) && s.M.ccw(M, N) != s.N.ccw(M, N);
    }
    Point its(Segment s) { return (N - M) * (s.N - s.M).cross(M - s.M) / (N - M).cross(s.N - s.M) + M; }
    vector <Point> cutP(vector <Point> &vecP) {
        vector <Point> vecAns;
        for (int i = 0; i < vecP.size(); ++i) {
            int iNext = (i + 1) % vecP.size();
            if (vecP[i].ccw(M, N) >= 0) vecAns.push_back(vecP[i]);
            if (vecP[i].ccw(M, N) * vecP[iNext].ccw(M, N) < 0) 
                vecAns.push_back(its(Segment(vecP[i], vecP[iNext])));
        }
        return vecAns;
    }
    vector <Point> cutC(Point p, T r) {
        vector <Point> vecAns;
        Point pa = p.proj(M, N), pb = (N - M) / (N - M).norm();
        T h = (p - pa).norm(), d = sqrt(r * r - h * h);
        vecAns = {pa - pb * d, pa + pb * d};
        return vecAns;
    }
    T its(vector <Point> &vecP) {
        T ans = 0; int n = vecP.size();
        vector <Point> vecP1;
        for (int i = 0; i < n; ++i) {
            int iPrev = (i - 1 + n) % n, iNext = (i + 1) % n, iNext2 = (i + 2) % n;
            Segment s = Segment(vecP[i], vecP[iNext]);
            if (!is_its(s)) continue;
            Point p = its(s);
            if (!vecP1.empty() && (p == vecP1[0] || p == vecP1.back())) continue;
            bool valid = false;
            bool a = !vecP[iPrev].ccw(M, N) && !vecP[i].ccw(M, N);
            bool b = !vecP[iNext].ccw(M, N) && !vecP[iNext2].ccw(M, N);
            if (a || b) {
                if (p == vecP[i]) {
                    if (vecP[iPrev].ccw(vecP[i], vecP[iNext]) > 0) valid = true;
                } else if (p == vecP[iNext]) {
                    if (vecP[i].ccw(vecP[iNext], vecP[iNext2]) > 0) valid = true;
                }
            } else if (p == vecP[i]) {
                if (vecP[iPrev].ccw(M, N) != vecP[iNext].ccw(M, N)) valid = true;
            } else if (p == vecP[iNext]) {
                if (vecP[i].ccw(M, N) != vecP[iNext2].ccw(M, N)) valid = true;
            } else valid = true;
            if (valid) vecP1.push_back(p);
        }
        sort(vecP1.begin(), vecP1.end());
        for (int i = 0; i + 1 < vecP1.size(); i += 2) ans += (vecP1[i] - vecP1[i + 1]).norm();
        return ans;
    }
};