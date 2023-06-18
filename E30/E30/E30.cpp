//Beatriz Bueno Almagro E09

#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

/*Vuelta atras de minimización
* Poda: se implementa un vector mat_min que aloja el precio más barato de cada producto en el supermercado en el que sea
* por cada funcion parcial sumamos todos los productos (de mat_min) que nos quedan, y si es mayor que la mejorsol
* cortamos esa rama ya que nunca llegaremos a una suma menor.
*/

const int MAX_PROD = 3;

bool esValida(const int i, vector<int> const& marcas) {
    return marcas[i] <= MAX_PROD;
}

bool esSolucion(const int m, const int k) {
    return k == m - 1;
}

bool esMejor(const int suma, const int sumamejor) {
    return sumamejor == - 1 || suma < sumamejor;
}

bool esCompletable(const int m, const int k) {
    return k < m - 1;
}

bool esPrometedor(const int suma, const int mejorsuma, const int mincoste) {
    int auxmincoste = suma + mincoste;
    return mejorsuma == -1 || auxmincoste < mejorsuma;
}

void compra(vector<vector<int>> const& mat, const int n, const int m, vector<int>& sol, int& suma, vector<int>& solmejor, int& sumamejor, int k, vector<int>& marcas, vector<int> const& matmin, int& mincoste) {
    for (int i = 0; i < n; i++) {
        sol[k] = i;
        suma += mat[i][k];
        marcas[i]++;
        mincoste -= matmin[k];
        if (esValida(i, marcas)) {
            if (esSolucion(m, k)) {
                if (esMejor(suma, sumamejor)) {
                    solmejor = sol;
                    sumamejor = suma;
                }
            }
            else if (esCompletable(m, k) && esPrometedor(suma, sumamejor, mincoste)) {
                compra(mat, n, m, sol, suma, solmejor, sumamejor, k + 1, marcas, matmin, mincoste);
            }
        }
        mincoste += matmin[k];
        marcas[i]--;
        suma -= mat[i][k];
    }
}

int compra(vector<vector<int>> const& mat, const int n, const int m) {
    vector<int> sol(m), solmejor(m), marcas(n);
    int sumamejor = -1, suma = 0;
    vector<int> matmin(m, -1);
    int auxmin = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matmin[j] == -1 || mat[i][j] < matmin[j]) {
                if (mat[i][j] < matmin[j])
                    auxmin -= matmin[j];
                auxmin += mat[i][j];
                matmin[j] = mat[i][j];
            }
        }
    }
    compra(mat, n, m, sol, suma, solmejor, sumamejor, 0, marcas, matmin, auxmin);
    return sumamejor;
}

void resuelveCaso() {
    //resuelve aqui tu caso
    int n, m;
    cin >> n >> m;
    vector <vector<int>> mat(n, vector<int> (m));
    //Lee los datos
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
        }
    }
    //Calcula el resultado
    int sumamejor = compra(mat, n, m);
    //Escribe el resultado
    if (sumamejor != -1)
        cout << sumamejor << "\n";
    else
        cout << "Sin solucion factible" << "\n";
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
