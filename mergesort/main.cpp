#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;
using namespace std::chrono;

void interclasare(vector<int> &v, int index_inceput, int inc1, int sf1, int inc2, int sf2){
    vector<int> merged(sf2 - inc1 + 1);
    int k = 0;
    while (inc1 <= sf1 && inc2 <= sf2){
        if (v[inc1] <= v[inc2]){
            merged[k] = v[inc1];
            inc1++;
        } else {
            merged[k] = v[inc2];
            inc2++;
        }
        k++;
    }
    while (inc1 <= sf1){
        merged[k] = v[inc1];
        k++;
        inc1++;
    }
    while (inc2 <= sf2){
        merged[k] = v[inc2];
        k++;
        inc2++;
    }
    for (int j = 0; j < k; j++){
        v[index_inceput + j] = merged[j];
    }
}

void sortare(vector<int> &v, int n){
    int size_v_intercl = 1;
    while (size_v_intercl < n){
        int i = 0;
        while (i < n){
            int inc1 = i, sf1 = i + size_v_intercl - 1, inc2 = i + size_v_intercl, sf2 = i + 2 * size_v_intercl - 1;
            if (inc2 < n){
                if (sf2 >= n) {
                    sf2 = n - 1;
                }
                interclasare(v, i, inc1, sf1, inc2, sf2);
            }
            i += 2 * size_v_intercl;
        }
        size_v_intercl *= 2;
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
        sortare(v, n);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Timpul de executare: " << duration.count() << " microsecunde" << endl;
    }
    return 0;
}
