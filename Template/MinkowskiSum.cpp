vector <Point> Minkowski(vector <Point> vecP1, vector <Point> vecP2) {
    int n1 = vecP1.size(), n2 = vecP2.size(), i1 = 0, i2 = 0;
    for (int i = 1; i < n1; ++i)
        if (vecP1[i].x < vecP1[i1].x || (vecP1[i].x == vecP1[i1].x && vecP1[i].y < vecP1[i1].y)) i1 = i;
    for (int i = 1; i < n2; ++i)
        if (vecP2[i].x < vecP2[i2].x || (vecP2[i].x == vecP2[i2].x && vecP2[i].y < vecP2[i2].y)) i2 = i;
    vector <Point> vecP = {vecP1[i1] + vecP2[i2]};
    for (int i = 1; i < n1 + n2; ++i) {
        int j1 = (i1 + 1) % n1, j2 = (i2 + 1) % n2;
        Point pa = vecP1[j1] + vecP2[i2], pb = vecP1[i1] + vecP2[j2], pc = vecP.back();
        if (pc.ccw(pa, pb) > 0 || pb.on(pa, pc)) {
            vecP.push_back(pa);
            i1 = j1;
        } else {
            vecP.push_back(pb);
            i2 = j2;
        }
    }
    int n = vecP.size();
    vector <Point> vecAns;
    for (int i = 0; i < n; ++i) {
        int ipre = (i - 1 + n) % n, inxt = (i + 1) % n;
        if (vecP[ipre].ccw(vecP[i], vecP[inxt])) vecAns.push_back(vecP[i]);
    }
    return vecAns;
}