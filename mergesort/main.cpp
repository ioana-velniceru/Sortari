#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;
using namespace std::chrono;

void interclasare(vector<int> &v, int inceput, int mijloc, int sfarsit){
    int n1 = mijloc - inceput + 1, n2 = sfarsit - mijloc;
    vector<int> v1(n1), v2(n2);
    for (int i = 0; i < n1; i++)
        v1[i] = v[i + inceput];
    for (int i = 0; i < n2; i++)
        v2[i] = v[i + mijloc + 1];
    int i = 0, j = 0, k = inceput;
    while (i < n1 && j < n2){
        if (v1[i] <= v2[j]){
            v[k] = v1[i];
            i++;
        } else {
            v[k] = v2[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        v[k] = v1[i];
        k++;
        i++;
    }
    while (j < n2){
        v[k] = v2[j];
        k++;
        j++;
    }
}

void sortare(vector<int> &v, int inceput, int sfarsit){
    int size_v_intercl, index_inceput;
    for (size_v_intercl = 1; size_v_intercl <= sfarsit; size_v_intercl *= 2){
        for (index_inceput = inceput; index_inceput < sfarsit; index_inceput += size_v_intercl * 2){
            int mijloc, index_sfarsit;
            if (index_inceput + size_v_intercl - 1 <= sfarsit){
                mijloc = index_inceput + size_v_intercl - 1;
            } else {
                mijloc = sfarsit;
            }
            if (index_inceput + size_v_intercl * 2 - 1 <= sfarsit){
                index_sfarsit = index_inceput + size_v_intercl * 2 - 1;
            } else {
                index_sfarsit = sfarsit;
            }
            interclasare(v, index_inceput, mijloc, index_sfarsit);
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
        if (n > 80000000){
            cout << "Algoritmul nu poate sorta" << endl;
        }
        else {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dist(0, nrmaxim);
            auto generator = bind(dist, gen);
            generate_n(v.begin(), n, generator);
            auto start = high_resolution_clock::now();
            sortare(v, 0, n - 1);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Timpul de executare: " << duration.count() << " microsecunde" << endl;
        }
    }
    return 0;
}
