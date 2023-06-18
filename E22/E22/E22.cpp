// NOMBRE Y APELLIDOS

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int tieneUno(int n) {
    if (n < 1)
        return n;
    if (n >= 1 && n < 10)
        return n - 1;
    int p = 1;
    while (n / p > 9)
        p = p * 10;
    int ultdig = n / p;
    if (ultdig != 1)
        return tieneUno(ultdig) * tieneUno(p - 1) + tieneUno(ultdig) + tieneUno(n % p);
    else
        return tieneUno(ultdig * p - 1);
}

bool resuelveCaso() {
    //Leer caso de prueba: cin>>...
    int n;
    cin >> n;
    if (!std::cin)
        return false;
    int c = tieneUno(n) + 1;
    //Resolver problema
    //Escribir resultado
    cout << c << "\n";
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