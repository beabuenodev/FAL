//Beatriz Bueno Almagro E09

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

/*
* + azul - 0
* + rojo - 1
* + verde - 2
*/

struct tColores {
    int azul;
    int rojo;
    int verde;
};

bool esValida(const tColores piezas, vector<int> const& sol, const tColores solpiezas, const int i, const int k) {
    if (i == 0)
        return piezas.azul >= solpiezas.azul;
    else if (i == 1)
        return piezas.rojo >= solpiezas.rojo;
    else
        return piezas.verde >= solpiezas.verde && sol[k - 1] != 2 && solpiezas.azul >= solpiezas.verde;
}

bool esSolucion(const int n, const tColores solpiezas, const int k) {
    return (solpiezas.rojo > (solpiezas.verde + solpiezas.azul));
}

void tratarSolucion(vector<int> const& sol) {
    for (int i = 0; i < sol.size(); i++) {
        switch (sol[i]) {
        case 0:
            cout << "azul ";
            break;
        case 1:
            cout << "rojo ";
            break;
        case 2:
            cout << "verde ";
            break;
        }
    }
    cout << '\n';
}

void torreColores(const tColores piezas, const int n, vector<int>& sol, tColores& solpiezas, int k, bool& haysol) {
    for (int i = 0; i < 3; i++) {
        sol[k] = i;
        if (i == 0)
            solpiezas.azul++;
        if (i == 1)
            solpiezas.rojo++;
        if (i == 2)
            solpiezas.verde++;
        if (esValida(piezas, sol, solpiezas, i, k)) {
            if (k + 1 == n) {
                if (esSolucion(n, solpiezas, k)) {
                    haysol = true;
                    tratarSolucion(sol);
                }
            }
            else {
                torreColores(piezas, n, sol, solpiezas, k + 1, haysol);
            }
        }
        if (i == 0)
            solpiezas.azul--;
        if (i == 1)
            solpiezas.rojo--;
        if (i == 2)
            solpiezas.verde--;
    }
}

void torreColores(const tColores piezas, const int n, bool& haysol) {
    vector<int> sol(n);
    sol[0] = 1;
    tColores solpiezas = { 0, 1, 0 };
    torreColores(piezas, n, sol, solpiezas, 1, haysol);
}

bool resuelveCaso() {

    //Leer caso de prueba: cin>>...
    int n;
    cin >> n;
    if (n == 0)
        return false;

    tColores piezas;
    cin >> piezas.azul;
    cin >> piezas.rojo;
    cin >> piezas.verde;
    //Resolver problema
    bool haysol = false;
    torreColores(piezas, n, haysol);
    //Escribir resultado
    if (!haysol)
        cout << "SIN SOLUCION\n";
    cout << " " << endl;
    return true;
}


int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}