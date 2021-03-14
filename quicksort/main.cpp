#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;
using namespace std::chrono;

vector<int> st(100000001);

void alegere_pivot(vector<int> &v, int inceput, int sfarsit){
    int mijloc = inceput + ((sfarsit - inceput) >> 1), aux;
    if (v[mijloc] < v[inceput]){
        aux = v[mijloc];
        v[mijloc] = v[inceput];
        v[inceput] = aux;
    }
    if (v[sfarsit] < v[inceput]){
        aux = v[sfarsit];
        v[sfarsit] = v[inceput];
        v[inceput] = aux;
    }
    if (v[mijloc] < v[sfarsit]){
        aux = v[mijloc];
        v[mijloc] = v[sfarsit];
        v[sfarsit] = aux;
    }
}

int impartire(vector<int> &v, int inceput, int sfarsit){
    alegere_pivot(v, inceput, sfarsit);
    int pivot = v[sfarsit];
    int aux, i = inceput;
    for (int j = inceput; j < sfarsit; j++){
        if (v[j] <= pivot){
            aux = v[j];
            v[j] = v[i];
            v[i] = aux;
            i++;
        }
    }
    aux = v[i];
    v[i] = v[sfarsit];
    v[sfarsit] = aux;
    return i;
}

void sortare(vector<int> &v, int inceput, int sfarsit){
    int top = 0;
    st[top] = inceput;
    top++;
    st[top] = sfarsit;
    while (top >= 0){
        sfarsit = st[top];
        top--;
        inceput = st[top];
        int poz_pivot = impartire(v, inceput, sfarsit);
        if (poz_pivot - 1 > inceput){
            st[top] = inceput;
            top++;
            st[top] = poz_pivot - 1;
            top++;
        }
        if (poz_pivot + 1 < sfarsit){
            st[top] = poz_pivot + 1;
            top++;
            st[top] = sfarsit;
            top++;
        }
        top--;
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
        if (n / nrmaxim > 1000 && n >= 10000000){
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
