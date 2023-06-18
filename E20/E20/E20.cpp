// Beatriz Bueno Almagro E09

#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct tBongo {
    int pos;
    bool sol;
};

tBongo bongo(vector<int> const& v, int i, int f, int x) {
    int m = (i + f) / 2;
    if (x + m == v[m])
        return { v[m], true };
    else if (i == f) return { -1, false };
    else {
        if (x + m > v[m])
            return bongo(v, m + 1, f, x);
        else
            return bongo(v, i, m, x);
    }
}

tBongo bongo(vector<int> const& v, int x) {
    return bongo(v, 0, v.size() - 1, x);
}

void resuelveCaso() {
    //resuelve aqui tu caso
    //Lee los datos
    int n, x, aux;
    vector<int> v;
    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        cin >> aux;
        v.push_back(aux);
    }
    //Calcula el resultado
    tBongo sol = bongo(v, x);
    //Escribe el resultado
    if (sol.sol)
        cout << sol.pos << '\n';
    else
        cout << "NO\n";
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


    unsigned int numCasos;
    std::cin >> numCasos;
    // Resolvemos
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }


#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}