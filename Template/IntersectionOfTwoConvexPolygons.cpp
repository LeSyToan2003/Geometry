vector <Point> IoCP(vector <Point> vecP1, vector <Point> vecP2) {
    vector <Point> vecAns;
    int n1 = vecP1.size(), n2 = vecP2.size();
    for (int i1 = 0; i1 < n1; ++i1)
        for (int i2 = 0; i2 < n2; ++i2) {
        Segment s1 = Segment(vecP1[i1], vecP1[(i1 + 1) % n1]);
        Segment s2 = Segment(vecP2[i2], vecP2[(i2 + 1) % n2]);
        if ((s1.N - s1.M).cross(s2.N - s2.M) != 0 && s1.is_its(s2)) vecAns.push_back(s1.its(s2));
    }
    for (auto p : vecP1) if (p.in_CP(vecP2)) vecAns.push_back(p);
    for (auto p : vecP2) if (p.in_CP(vecP1)) vecAns.push_back(p);
    return ConvexHull(vecAns);
}