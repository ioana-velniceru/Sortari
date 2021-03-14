#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;
using namespace std::chrono;

vector<int> frecv(100001);

void sortare(int n, vector<int> &v){
    int maxim = -1;
    for (int i = 0; i < n; i++){
        frecv[v[i]]++;
        if (v[i] > maxim){
            maxim = v[i];
        }
    }
    int j = 0;
    for (int i = 0; i <= maxim; i++){
        while (frecv[i]){
            v[j] = i;
            j++;
            frecv[i]--;
        }
    }
}

int main()
{
    int t;
    cout << "T = ";
    cin >> t;
    cout << endl;
    for (int i = 0; i < t; i++){
        int n, nrmaxim;
        cout << "N = ";
        cin >> n;
        vector<int> v(n);
        cout << "Max = ";
        cin >> nrmaxim;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(0, nrmaxim);
        auto generator = bind(dist, gen);
        generate_n(v.begin(), n, generator);
        auto start = high_resolution_clock::now();
        sortare(n, v);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Timpul de executare: " << duration.count() << " microsecunde" << endl;
    }
    return 0;
}
