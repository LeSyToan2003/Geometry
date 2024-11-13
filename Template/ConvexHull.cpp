vector <Point> ConvexHull(vector <Point> &vecP) {
    sort(vecP.begin(), vecP.end());
    int n = vecP.size(), nAns = 0;
    if (n < 3) return vecP;
    vector <Point> vecAns = vecP;
    vecAns.resize(n + 1);
    for (int i = 1; i < n; ++i)
        if (i == n - 1 || vecP[0].ccw(vecP[i], vecP[n - 1]) > 0) {
            while (nAns > 0 && vecAns[nAns - 1].ccw(vecAns[nAns], vecP[i]) <= 0) nAns--;
            vecAns[++nAns] = vecP[i];
        }
    for (int i = n - 2, j = nAns; i >= 0; --i)
        if (i == 0 || vecP[n - 1].ccw(vecP[i], vecP[0]) > 0) {
            while (nAns > j && vecAns[nAns - 1].ccw(vecAns[nAns], vecP[i]) <= 0) nAns--;
            vecAns[++nAns] = vecP[i];
        }
    vecAns.resize(nAns);
    return vecAns;
}