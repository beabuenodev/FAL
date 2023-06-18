//Beatriz Bueno Almagro E09

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int num_digits(int n) {
    int c = 0;
    if (n == 0)
        return 1;
    while (n != 0) {
        n /= 10;
        c++;
    }

    return c;
}

void multiplicativo(int n, int pow10, int mult, int& c) {
    int div = pow(10, pow10 - 1);
    int aux = (n / div) % 10;

    if (aux == mult % 10)
        c++;

    if (pow10 == 1) 
        return;
    else
        multiplicativo(n, pow10 - 1, mult * aux, c);
}

void resuelveCaso() {
    //resuelve aqui tu caso
    //Lee los datos
    int n;
    cin >> n;
    //Calcula el resultado
    //Escribe el resultado
    int sol = 0;

    int pow = num_digits(n);
    multiplicativo(n, pow, 1, sol);
    cout << sol << endl;
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