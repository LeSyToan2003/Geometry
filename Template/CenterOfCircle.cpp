Point CoC(Point pa, Point pb, Point pc) {
    Point p1 = pc - pa, p2 = pb - pa;
    return pa + (p1 * p2.norm2() - p2 * p1.norm2()).rotating(PI / 2) / p1.cross(p2) / 2;
}