#include <bits/stdc++.h>
#include <chrono>

using namespace std;

vector<int> costo_insercion(26);
vector<int> costo_eliminacion(26);
vector<vector<int>> costo_sustitucion(26, vector<int>(26));
vector<vector<int>> costo_transposicion(26, vector<int>(26));

void cargarVector(const string &archivo, vector<int> &vector_costos, int tamaño) {
    ifstream archivoEntrada(archivo);
    if (!archivoEntrada.is_open()) {
        cerr << "Error al abrir el archivo " << archivo << endl;
        exit(EXIT_FAILURE);
    }

    int contador = 0;
    for (int i = 0; i < tamaño; ++i) {
        archivoEntrada >> vector_costos[i];
        contador++;
    }
    if (contador != tamaño) {
        cerr << "Tamaño incorrecto en el archivo " << archivo << endl;
        exit(EXIT_FAILURE);
    }
}

void cargarMatriz(const string &archivo, vector<vector<int>> &matriz_costos, int tamaño) {
    ifstream archivoEntrada(archivo);
    if (!archivoEntrada.is_open()) {
        cerr << "Error al abrir el archivo " << archivo << endl;
        exit(EXIT_FAILURE);
    }
    int filas = 0, columnas = 0;
    for (int i = 0; i < tamaño; ++i) {
        for (int j = 0; j < tamaño; ++j) {
            archivoEntrada >> matriz_costos[i][j];
            columnas++;
        }
        filas++;
    }
    if (filas != tamaño || columnas != tamaño * tamaño) {
        cerr << "Tamaño incorrecto en el archivo " << archivo << endl;
        exit(EXIT_FAILURE);
    }
}

int costo_sub(char a, char b) {
    return costo_sustitucion[a - 'a'][b - 'a'];
}

int costo_ins(char b) {
    return costo_insercion[b - 'a'];
}

int costo_del(char a) {
    return costo_eliminacion[a - 'a'];
}

int costo_trans(char a, char b) {
    return costo_transposicion[a - 'a'][b - 'a'];
}

int FuerzaBrutaDistanciaMinima(string cadena1, string cadena2, int i, int j) {
    if (i == 0) {
        int costo = 0;
        for (int k = 0; k < j; ++k) costo += costo_ins(cadena2[k]);
        return costo;
    }
    if (j == 0) {
        int costo = 0;
        for (int k = 0; k < i; ++k) costo += costo_del(cadena1[k]);
        return costo;
    }

    int costoSustituir = FuerzaBrutaDistanciaMinima(cadena1, cadena2, i - 1, j - 1) + costo_sub(cadena1[i - 1], cadena2[j - 1]);
    int costoInsertar = FuerzaBrutaDistanciaMinima(cadena1, cadena2, i, j - 1) + costo_ins(cadena2[j - 1]);
    int costoEliminar = FuerzaBrutaDistanciaMinima(cadena1, cadena2, i - 1, j) + costo_del(cadena1[i - 1]);

    int costo = min({costoSustituir, costoInsertar, costoEliminar});

    if (i > 1 && j > 1 && cadena1[i - 1] == cadena2[j - 2] && cadena1[i - 2] == cadena2[j - 1]) {
        costo = min(costo, FuerzaBrutaDistanciaMinima(cadena1, cadena2, i - 2, j - 2) + costo_trans(cadena1[i - 1], cadena1[i - 2]));
    }

    return costo;
}

int main() {
    cargarVector("cost_insert.txt", costo_insercion, 26);
    cargarVector("cost_delete.txt", costo_eliminacion, 26);
    cargarMatriz("cost_replace.txt", costo_sustitucion, 26);
    cargarMatriz("cost_transpose.txt", costo_transposicion, 26);

    int configuracion = 0;

    cout << "Selecciona como quieres ingresar los datos:" << endl;

    cout << "Selecciona 0 para entrada por consola" << endl;

    cout << "Selecciona 1 para entrada por archivo" << endl;

    cin >> configuracion;

    if(configuracion) {

        ifstream archivo("entrada.txt");
        if (!archivo.is_open()) {
            cerr << "Error al abrir el archivo." << endl;
            return EXIT_FAILURE;
        }

        int n;
        archivo >> n;
        string cadena1, cadena2;

        for (int i = 0; i < n; ++i) {
            archivo >> cadena1 >> cadena2;
            auto inicio = chrono::high_resolution_clock::now();
            int resultado = FuerzaBrutaDistanciaMinima(cadena1, cadena2, cadena1.size(), cadena2.size());
            auto fin = chrono::high_resolution_clock::now();

            chrono::duration<double> duracion = fin - inicio;
            cout << "S1: " << cadena1 << "\t" << "S2: " << cadena2 << endl;
            cout << "Distancia mínima de edición: " << resultado << endl;
            cout << "Tiempo de ejecución: " << duracion.count() << " segundos" << endl;

            cout << "Memoria utilizada por la tabla de costos (aproximada): " << (26 * sizeof(int) * 3 + 26 * 26 * sizeof(int) * 2) / 1024.0 << " KB\n" << endl;


        }

        archivo.close();
    } else {
        string cadena1, cadena2;
        cout << "Ingrese la primera cadena: ";
        cin >> cadena1;
        cout << "Ingrese la segunda cadena: ";
        cin >> cadena2;

        auto inicio = chrono::high_resolution_clock::now();
        int resultado = FuerzaBrutaDistanciaMinima(cadena1, cadena2, cadena1.size(), cadena2.size());
        auto fin = chrono::high_resolution_clock::now();

        chrono::duration<double> duracion = fin - inicio;
        cout << "Distancia mínima de edición: " << resultado << endl;
        cout << "Tiempo de ejecución: " << duracion.count() << " segundos" << endl;

        cout << "Memoria utilizada por la tabla de costos (aproximada): " << (26 * sizeof(int) * 3 + 26 * 26 * sizeof(int) * 2) / 1024.0 << " KB" << endl;
    }

    return 0;
}
