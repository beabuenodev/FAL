//Beatriz Bueno Almagro E09

#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

/* Este ejercicio esta resuelto por vuelta atrás
*  - EXPLICACIÖN ARBOL EXPLORACION
*       El arbol de exploración de este ejercicio esta planteado con n nodos iniciales, siendo n el numero de artistas, y se divide en los artistas restantes para llenar los huecos que quedan.
*       el arbol tiene n niveles, también siendo n el numero de artistas
*  - MARCADORES
*       Usamos un vector de booleanos del tamaño del numero de artistas para indicar con true los artistas que ya están colocados, además usamos el vector de solucion a modo de marcador ya que
*       lo usamos para ver los artistas anteriores y comprobar vetos
*  - PODAS
*       1) Llevar la máxima donación de cada artista en cualquier actuación. Con una solución parcial, el mejor de los casos es que el resto de de actuaciones recibieran esa máxima donación. Si ese
*          valor es menor que el que llevamos hasta ahora, podamos.
*       2) Llevar para cada actuación, la máxima donación que se puede recibir. Cogemos la solución parcial, y el mejor de los casos es que las actuaciones que quedan recibieran su máxima donación. 
*          Si ese valor es meor que el que llevamos hasta ahora, podamos
*       Usamos la más restrictiva, la segunda
*/

bool esValida(const int n, vector<vector<bool>> const& vetos, vector<int> const& sol, vector<bool> const& marcas, const int k, const int i) {
    if (k == 0)
        return true;
    return !marcas[i] && vetos[i][sol[k - 1]];
}

bool esSolucion(const int n, const int k) {
    return n == k + 1;
}

bool esPrometedor(const int suma, const int mejorsuma, const int maxposible) {
    return (suma + maxposible) > mejorsuma;
}

void vueltaAtras(const int n, vector<vector<int>> const& estimaciones, vector<vector<bool>> const& vetos, vector<int>& sol, int& suma, int& mejorsuma, vector<bool>& marcas,
        int& maxposible, vector<int> const& maxdonaciones, int k) {
    for (int i = 0; i < n; i++) {
        sol[k] = i;
        suma += estimaciones[k][i];
        maxposible -= maxdonaciones[k];
        if (esValida(n, vetos, sol, marcas, k, i)) {
            if (esSolucion(n, k)) {
                if (suma > mejorsuma)
                    mejorsuma = suma;
            }
            else if (k < n-1 && esPrometedor(suma, mejorsuma, maxposible)) {
                marcas[i] = true;
                vueltaAtras(n, estimaciones, vetos, sol, suma, mejorsuma, marcas, maxposible, maxdonaciones, k + 1);
                marcas[i] = false;
            }
        } 
        maxposible += maxdonaciones[k];
        suma -= estimaciones[k][i];
    }
}

int vueltaAtras(const int n, vector<vector<int>> const& estimaciones, vector<vector<bool>> const& vetos) {
    vector<int> sol(n), maxdonaciones(n, -1);
    int suma = 0, mejorsuma = -1, maxposible = 0;
    vector<bool> marcas(n, false);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (maxdonaciones[j] == -1 || maxdonaciones[j] < estimaciones[i][j]) {
                if (maxdonaciones[j] != -1)
                    maxposible -= maxdonaciones[j];
                maxdonaciones[j] = estimaciones[i][j];
                maxposible += maxdonaciones[j];
            }
        }
    }
    vueltaAtras(n, estimaciones, vetos, sol, suma, mejorsuma, marcas, maxposible, maxdonaciones,0);
    return mejorsuma;
}

void resuelveCaso() {
    //resuelve aqui tu caso
    //Lee los datos
    int n, aux;
    cin >> n;
    vector<vector<int>> estimaciones(n, vector<int>(n));
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++)
            cin >> estimaciones[i][j];
    vector<vector<bool>> vetos(n, vector<bool>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> aux;
            if (aux == 0)
                vetos[i][j] = false;
            else
                vetos[i][j] = true;
        }
    }
    //Calcula el resultado
    //Escribe el resultado
    int sol = vueltaAtras(n, estimaciones, vetos);
    if (sol == -1)
        cout << "NEGOCIA CON LOS ARTISTAS" << endl;
    else
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