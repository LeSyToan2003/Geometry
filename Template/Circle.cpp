struct Circle {
    typedef double T; const T PI = acos(-1); Point pcent; T r;
    Circle() {} Circle(Point _pcent, T _r) { pcent = _pcent, r = _r; }
    vector <Point> its(Circle c) {
        T d = (pcent - c.pcent).norm(), a = acos((r * r + d * d - c.r * c.r) / (2 * r * d)); 
        T l = r * cos(a), h = r * sin(a);
        Point pa = (c.pcent - pcent) * l / d + pcent, pb = (pcent - pa) * h / (pcent - pa).norm() + pa;
        vector <Point> vacAncy = {pb.rotating(pa, PI / 2), pb.rotating(pa, - PI / 2)};
        return vecAns;
    }
};