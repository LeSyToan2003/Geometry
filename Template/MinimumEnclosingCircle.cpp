pair <Point, ld> MEC(vector <Point> &vecP) {
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count()); 
    shuffle(vecP.begin(), vecP.end(), rnd);
    Point pcent = vecP[0]; 
    ld r = 0;
    for (int i = 0; i < vecP.size(); ++i) {
        if (r < (pcent - vecP[i]).norm()) {
        pcent = vecP[i], r = 0;
        for (int j = 0; j < i; ++j) if (r < (pcent - vecP[j]).norm()) {
            pcent = (vecP[i] + vecP[j]) / 2, r = (pcent - vecP[i]).norm();
            for (int k = 0; k < j; ++k) if (r < (pcent - vecP[k]).norm())
                pcent = CoC(vecP[i], vecP[j], vecP[k]), r = (pcent - vecP[i]).norm();
            }
        }
    }
    return {pcent, r};
}