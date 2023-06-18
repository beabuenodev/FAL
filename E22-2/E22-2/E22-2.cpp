//Beatriz Bueno Almagro E09

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

bool tieneAlgunUno(long long int n) {
    while ((n != 0) && (n % 10 != 1)) {
        n = n / 10;
    }

    if (n % 10 == 1) return true;
    else return false;
}

long long int tieneUno(long long int n) { //Coste - O(log n)
    if (n == 0) return 1;
    long long int sol = 0, parte = n / 10, ultimo = n % 10;

    for (int i = 0; i <= ultimo; i++) {
        if (!tieneAlgunUno(10 * parte + i)) sol++;
    }

    if (parte) sol += tieneUno(parte - 1) * 9;
    return sol;
}

bool resuelveCaso() {
    //Leer caso de prueba: cin>>...
    long long int n;
    cin >> n;
    if (!std::cin)
        return false;
    cout << tieneUno(n) << "\n";

    //Resolver problema
    //Escribir resultado
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