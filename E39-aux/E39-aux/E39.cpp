//Beatriz Bueno Almagro E09

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

struct tCinta {
    int uno, dos;
};

struct tCancion {
    int dur, punt;
};

/*
* Este ejercicio está hecho por vuelta atrás
*  - Explicación arbol de exploración
*       El arbol de exploración de este ejercicio se compone por n nodos raiz, siendo n el numero de canciones, que desembocan en las canciones restantes. El arbol
*       tiene n niveles.
*  - Explicación marcas 
*       Guardamos un vector de booleanos con tamaño n, siendo n el número de canciones. Al no poder repetirse las canciones, usamos esta marca para saber si estamos
*       intentando añadir una canción ya utilizada. Si una canción i ya se ha utilizado, marcas[i] = true, false en caso contrario
*  - Explicación podas
*       Inicializamos una variable int con el máximo de puntuación alcanzable hasta el momento (sin tener en cuenta la duracion de las canciones) que vamos actualizando. Cuando añadimos una cancion
*       a nuestra solucion, le quitamos su puntuacion. Si a la puntuacion total de una solucion parcial le añadimos esta variable y se queda por debajo de la suma maxima, podamos.
*       Añadimos otra poda para la duración. Guardamos el mínimo de duración de las canciones. Si en una rama si le sumamos el min de duracion se queda por encima de la capacidad máxima,
*       entonces no es completable.
*/

pair<bool, int> siguienteHijoNivel(const int cinta, vector<tCancion> const& v, tCinta& sol, const int i) {
    if ((cinta - sol.uno) >= v[i].dur) {
        sol.uno += v[i].dur;
        return { true, 1 };
    }
    else if ((cinta - sol.dos) >= v[i].dur) {
        sol.dos += v[i].dur;
        return { true, 2 };
    }
    else
        return { false, 0 };
}

void deshacerHijoNivel(vector<tCancion> const& v, tCinta& sol, const int i, const int side) {
    if (side == 1)
        sol.uno -= v[i].dur;
    else if (side == 2)
        sol.dos -= v[i].dur;
}

bool esValida(const bool esvalida, const int i, vector<bool> const& marcas) {
    return esvalida && !marcas[i];
}

bool esPrometedor(const int suma, const int mejorsuma, const int max_alcanzable) {
    return suma + max_alcanzable > mejorsuma;
}

bool esCompletable(const tCinta sol, const int min_dur, const int cinta) {
    return !(sol.uno + min_dur > cinta && sol.dos + min_dur > cinta) || sol.uno + sol.dos < cinta*2;
}

void vueltaAtras(const int n, const int cinta, vector<tCancion> const& v, tCinta& sol, int& suma, int& mejorsuma, vector<bool>& marcas, int& max_alcanzable, const int min_dur,int k) {
    for (int i = 0; i < n; i++) {
        pair<bool,int> esvalida = siguienteHijoNivel(cinta, v, sol, i); //guardamos en sol el siguiente hijo y a la vez guardamos  si la solucion es valida o no (ha podido guardarse en la cinta)
        if (esValida(esvalida.first, i, marcas)) {
            suma += v[i].punt;
            max_alcanzable -= v[i].punt;
            if (suma > mejorsuma) {
                mejorsuma = suma;
            }
            else if (k < n - 1 && esPrometedor(suma, mejorsuma, max_alcanzable) && esCompletable(sol, min_dur, cinta)) {
                marcas[i] = true;
                vueltaAtras(n, cinta, v, sol, suma, mejorsuma, marcas, max_alcanzable, min_dur, k + 1);
                marcas[i] = false;
            }
            suma -= v[i].punt;
            max_alcanzable += v[i].punt;
        }
        deshacerHijoNivel(v, sol, i, esvalida.second);
    }
}

int vueltaAtras(const int n, const int cinta, vector<tCancion> const& v) {
    tCinta sol = { 0, 0 };
    int suma = 0, mejorsuma = -1;
    vector<bool> marcas(n, false);
    int max_alcanzable = 0;
    int min_dur = -1;
    for (int i = 0; i < n; i++) {
        max_alcanzable += v[i].punt;
        if (min_dur == -1 || v[i].dur < min_dur)
            min_dur = v[i].dur;
    }
    vueltaAtras(n, cinta, v, sol, suma, mejorsuma, marcas, max_alcanzable, min_dur, 0);
    return mejorsuma;
}

bool resuelveCaso() {

    //Leer caso de prueba: cin>>...

    int n;
    cin >> n;

    if (n == 0)
        return false;

    int cinta;
    cin >> cinta;

    vector<tCancion> v;

    for (int i = 0; i < n; i++) {
        tCancion aux;
        cin >> aux.dur >> aux.punt;
        v.push_back(aux);
    }

    //Resolver problema
    cout << vueltaAtras(n, cinta, v) << '\n';
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