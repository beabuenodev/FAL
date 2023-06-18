//Beatriz Bueno Almagro E09

#include <iostream>
#include <fstream>
using namespace std;

/*
* Analisis de coste:
*  - Ecuación de recurrencia: (siendo n el numero de digitos)
*       T(n) = c0            si n = 1
*              c1 + T(n - 1) si n > 1
*  - Despliegue:
*       T(n) = c1 + T(n - 1)
*            = c1 + c1 + T(n - 2)
*            = c1*k + T(n - k)
*  - Postulado:
*       n - k = 1 <-> k = 1 + n
*       T(n) = c1*(1 + n) + T(n - (1 + n)) = c1 + c1*n + T(1) = c1 + c0 + c1*n -> O(n) 
*  - Coste: O(n) siendo n el numero de digitos de n
*/

int resolver(int n, int ant) {
    if (n < 10) {
        if (n >= ant)
            return n;
        else
            return 0;
    }
    else {
        int ult = n % 10;
        if (ult < ant)
            return resolver(n / 10, ant);
        else
            return resolver(n / 10, ult)*10 + ult;
    }
}

void resuelveCaso() {
    //resuelve aqui tu caso
    //Lee los datos
    int n;
    cin >> n;
    //Calcula el resultado
    //Escribe el resultado
    cout << resolver(n, -1) << endl;
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