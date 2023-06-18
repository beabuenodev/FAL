//Beatriz Bueno Almagro E09


#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct tSol {
    int sumapar, sumaimp, prodpar, prodimp;
    bool extrano;
};

tSol dyv(vector<int> const& v, int ini, int fin) {
    if (fin - ini == 0) {
        if (v[ini] % 2 == 0)
            return { v[ini], 0, v[ini], 1, true };
        else
            return { 0, v[ini], 1, v[ini], true };
    }
    else {
        int m = (ini + fin) / 2;
        tSol izq = dyv(v, ini, m);
        tSol der = dyv(v, m + 1, fin);
        tSol sol;
        sol.extrano = ((izq.sumapar + izq.prodimp) <= (der.prodpar + der.sumaimp)) && (izq.extrano || der.extrano);

        sol.sumapar = izq.sumapar + der.sumapar;
        sol.sumaimp = izq.sumaimp + der.sumaimp;

        sol.prodpar = izq.prodpar * der.prodpar;
        sol.prodimp = izq.prodimp * der.prodimp;

        return sol;
    }
}

void resuelveCaso() {
    //resuelve aqui tu caso
    //Lee los datos
    int n, aux;
    vector<int> v;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> aux;
        v.push_back(aux);
    }
    //Calcula el resultado
    bool sol = dyv(v, 0, v.size() - 1).extrano;
    //Escribe el resultado
    if (sol)
        cout << "SI" << '\n';
    else
        cout << "NO" << '\n';
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