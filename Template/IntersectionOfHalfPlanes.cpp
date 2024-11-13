vector <Point> IoHP(vector <Segment> vecS) {
    deque <Segment> dqS;
    deque <Point> dqP;
    for (auto s : vecS) {
        while (dqP.size() && dqP.back().ccw(s.M, s.N) < 0) dqS.pop_back(), dqP.pop_back();
        while (dqP.size() && dqP.front().ccw(s.M, s.N) < 0) dqS.pop_front(), dqP.pop_front();
        if (dqS.size()) dqP.push_back(s.its(dqS.back()));
        dqS.push_back(s);
    }
    while (dqS.size() > 2 && dqP.back().ccw(dqS.front().M, dqS.front().N) < 0) 
        dqS.pop_back(), dqP.pop_back();
    while (dqS.size() > 2 && dqP.front().ccw(dqS.back().M, dqS.back().N) < 0) 
        dqS.pop_front(), dqP.pop_front();
    dqP.push_back(dqS.front().its(dqS.back()));
    vector <Point> vecAns(dqP.begin(), dqP.end());
    return vecAns;
}