#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;
// 1
void enlarge(vector<int> &x) {
    vector<int>::iterator it;
    for (it = x.begin(); it != x.end() - 1; it++) {
        it = x.insert(it + 1, (*it + *(it + 1)) / 2);
    }
}

//2
void del(vector<int>& x) {
    vector<int>::iterator it;
    for (it = x.begin(); it < x.end() - 2; it++) {
        it = x.erase(it);
    }
    if (it != x.end())
        x.erase(it);
}

//4
vector<int> concat(vector<int> x, vector<int> y) {
    vector<int> res;
    res.resize(x.size() + y.size());
    copy(x.begin(), x.end(), res.begin());
    copy(y.begin(), y.end(), res.begin() + x.size());
    return res;
}

//5
vector<int> repeat(vector<int> v, int n) {
    vector<int> x;
    x.resize(v.size() * n);
    for (int i = 0; i < n; i++) {
        copy(v.begin(), v.end(), x.begin() + i * v.size());
    }
    return x;
}

//6
vector<int>::iterator second_occure(vector<int> &v, int x) {
    vector<int>::iterator it;
    it = find(v.begin(), v.end(), x);
    if (it != v.end()) 
        it = find(it + 1, v.end(), x);
    return it;
}

//7
vector<int>::reverse_iterator last_occure(vector<int> &v, int x) {
    auto it = find(v.rbegin(), v.rend(), x);
    return it;
}

//8
bool subseq(vector<int> x, vector<int> y) {
    auto it = y.begin();
    for (int t : x) {
        it = find(it + 1, y.end(), t);
        if (it == y.end())
            return false;
    }
    return true;
}

//9
int lastInSort(vector<int> x, int n) {
    auto it = upper_bound(x.begin(), x.end(), n);
    return (int)(it - 1 - x.begin());
}

//10
pair<int, int> findCloseReal(vector<double> x, double n) {
    auto itS = lower_bound(x.begin(), x.end(), n);
    if (abs(*itS - n) < 1e-10)
        return { (int)(itS - x.begin()), (int)(itS - x.begin()) };
    else 
        return { (int)(itS - 1 - x.begin()), (int)(itS - x.begin()) };
}

int main(){
    vector<int> a;
    a = { 1, 5, 11, 3, 3};
    enlarge(a);
    for (auto x : a)
        cout << x << " ";
    cout << endl;

    del(a);
    for (auto x : a)
        cout << x << " ";
    cout << endl;
    
//3
    vector<int> v = { 1, 2, 3, 4, 5 };
    int t[5] = { 14, 23, 3, 6, 7 };
    copy(v.begin(), v.end(), t);
    for (auto x : t)
        cout << x << " ";
    cout << endl;

    vector<int> b;
    b = concat(a, v);
    for (auto x : b)
        cout << x << " ";
    cout << endl;

    b = repeat(v, 3);
    for (auto x : b)
        cout << x << " ";
    cout << endl;

    vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    vector<int> s = { 3, 5, 7, 8 };
    cout << subseq(s, data) << endl;
    
    cout << lastInSort(data, 4) << endl;
    vector<double> dataReal = { 1.251, 4.32, 7.314, 10.5, 15.8, 19.21, 23.5, 28.34 };
    auto res = findCloseReal(dataReal, 12.6);
    cout << res.first << " " << res.second << endl;
}