#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;
using namespace std::chrono;

int numar_maxim(int n, vector<int> &v){
    int maxim = v[0];
    for (int i = 1; i < n; i++){
        if (v[i] > maxim){
            maxim = v[i];
        }
    }
    return maxim;
}

void sortare(int n, vector<int> &v){
    int cifra = 1, putere = 0;
    vector<int> temp(n);
    int maxim = numar_maxim(n, v);
    while (maxim >= cifra){
        int nr_el_bucket[2];
        nr_el_bucket[0] = 0;
        nr_el_bucket[1] = 0;
        for (int i = 0; i < n; i++){
            nr_el_bucket[(v[i] >> putere) & 1] ++;
        }
        int j = 0, k = nr_el_bucket[0];
        for (int i = 0; i < n; i++){
            if (((v[i] >> putere) & 1) == 0){
                temp[j] = v[i];
                j++;
            } else {
                temp[k] = v[i];
                k++;
            }
        }
        for (int i = 0; i < n; i++){
            v[i] = temp[i];
        }
        cifra *= 2;
        putere++;
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
