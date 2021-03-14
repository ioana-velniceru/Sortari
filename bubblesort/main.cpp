#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;
using namespace std::chrono;

void sortare(int n, vector<int> &v){
    int intersch = 1;
    while (intersch){
        intersch = 0;
        for (int i = 0; i < n; i++){
            if (v[i] > v[i + 1]){
                int aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;
                intersch = 1;
            }
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
        if (n > 80000){
            cout << "Algoritmul nu poate sorta" << endl;
        }
        else {
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

    }
        return 0;
}
