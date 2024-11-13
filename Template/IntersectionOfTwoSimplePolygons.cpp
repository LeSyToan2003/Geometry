double IoSP(vector <Point> vecP1, vector <Point> vecP2) {
    int n1 = vecP1.size(), n2 = vecP2.size();
    double ans = 0; 
    Point p = Point(- 1e9, - 1e9);
    for (int i1 = 0; i1 < n1; ++i1)
        for (int i2 = 0; i2 < n2; ++i2)
            if (p.ccw(vecP1[i1], vecP1[(i1 + 1) % n1]) && p.ccw(vecP2[i2], vecP2[(i2 + 1) % n2])) {
                vector <Point> vecP3 = {p, vecP1[i1], vecP1[(i1 + 1) % n1]};
                vector <Point> vecP4 = {p, vecP2[i2], vecP2[(i2 + 1) % n2]};
                vector <Point> vecP5 = IoCP(vecP3, vecP4);
                double a3 = Area(vecP3), a4 = Area(vecP4);
                int a = (a3 > 0 ? 1 : - 1)), b = (a4 > 0 ? 1 : - 1));
                ans += Area(vecP5) * (eq(a3, 0) ? 0 : * (eq(a4, 0) ? 0 : ;
            }
    return abs(ans);
}