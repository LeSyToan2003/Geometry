pair <int, int> Tangents(vector <Point> &vecP, Point p) {
    int n = vecP.size(); pair <int, int> ans;
    if (p.ccw(vecP[n - 1], vecP[0]) < 0) {
        int l = 0, r = n;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (p.ccw(vecP[n - 1], vecP[m]) >= 0 && p.ccw(vecP[m], vecP[m - 1]) >= 0) r = m;
            else l = m;
        }
        ans.first = l;
        l = - 1, r = n - 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (p.ccw(vecP[0], vecP[m]) <= 0 && p.ccw(vecP[m], vecP[m + 1]) <= 0) l = m;
            else r = m;
        }
        ans.second = r;
    } else {
        int l = - 1, r = n - 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (p.ccw(vecP[0], vecP[m + 1]) >= 0 && p.ccw(vecP[m], vecP[m + 1]) > 0) l = m;
            else r = m;
        }
        ans.first = r;
        l = 0, r = n;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (p.ccw(vecP[n - 1], vecP[m - 1]) <= 0 && p.ccw(vecP[m], vecP[m - 1]) < 0) r = m;
            else l = m;
        }
        ans.second = l;
    }
    if (vecP[(ans.first + 1) % n].on(vecP[ans.first], p)) ans.first = (ans.first + 1) % n;
    if (vecP[(ans.first - 1 + n) % n].on(vecP[ans.first], p)) ans.first = (ans.first - 1 + n) % n;
    if (vecP[(ans.second + 1) % n].on(vecP[ans.second], p)) ans.second = (ans.second + 1) % n;
    if (vecP[(ans.second - 1 + n) % n].on(vecP[ans.second], p)) ans.second = (ans.second - 1 + n) % n;
    return ans;
}