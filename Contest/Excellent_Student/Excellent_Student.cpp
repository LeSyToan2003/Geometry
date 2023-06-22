#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, k;
vector <pair <int, int>> vecObject;

void Task() {
    ios_base :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    if (fopen("test.inp", "r")) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
    }
}

void Solve() {
    cin >> n >> k;
    vecObject.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> vecObject[i].second >> vecObject[i].first;
        // vecObject[i] = {v,m};
    }
    set <pair <int, int>> setBag;
    for (int i = 0; i < k; ++i) {
        int c;
        cin >> c;
        setBag.insert({c, i});
        // Mỗi chiếc túi có giá trị c và nhãn i
    }

    sort(vecObject.begin(), vecObject.end());
    // Sắp xếp đồ vật theo tăng dần giá trị v

    ll ans = 0;
    for (int i = n - 1; i >= 0 && !setBag.empty(); --i) {
        int weight = vecObject[i].second;
        setBag.insert({weight, - 1});
        auto it = setBag.find({weight, - 1});
        it++;
        // Chiếc túi cần tìm nằm ngay sau giá trị {weight, -1} trong set
        if (it != setBag.end()) {
            setBag.erase(it);
            // Nếu tìm thấy, xóa chiếc túi đó đi và cộng giá trị của đồ vật vào đáp án
            ans += (ll)vecObject[i].first;
        }
        setBag.erase({weight, - 1});
    }

    cout << ans;
}

int main() {
    Task();
    Solve();
}
