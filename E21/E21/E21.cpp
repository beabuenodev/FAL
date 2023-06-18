//Beatriz Bueno Almagro E09

#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct tPeso {
    int peso;
    int dist;
};

struct tSol {
    bool equilibrio;
    int sumapeso;
};

/*
* El caso base es cuando nos encontramos con un peso y no con un submovil. Recorremos el móvil como un árbol, descubriendo recursivamente
* submóviles (paso recursivo) hasta que nos encontramos con un peso individual (caso base)
*/

tSol resolver(tPeso peso) {
    tPeso izq, der;
    if (peso.peso != 0) //CB: nos encontramos un peso y no otro submovil
        return { true, peso.peso };
    else { //Nos encontramos un submovil.
        cin >> izq.peso >> izq.dist >> der.peso >> der.dist;
        
        tSol izqsol = resolver(izq);
        tSol dersol = resolver(der);
        tSol sol;
        bool equilaux = (izqsol.sumapeso * izq.dist) == (dersol.sumapeso * der.dist);
        if (izqsol.equilibrio && dersol.equilibrio && equilaux)
            sol.equilibrio = true;
        else
            sol.equilibrio = false;
        sol.sumapeso = izqsol.sumapeso + dersol.sumapeso;
        return sol;
    }
}

void resuelveCaso() {
    //resuelve aqui tu caso
    tPeso raiz = { 0,0 };
    tSol sol = resolver(raiz);
    //Escribe el resultado
    if (sol.equilibrio)
        cout << "SI\n";
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