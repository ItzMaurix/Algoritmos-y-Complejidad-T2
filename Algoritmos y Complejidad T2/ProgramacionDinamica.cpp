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

int costoSubstitucion(char a, char b) {
    return costo_sustitucion[a - 'a'][b - 'a'];
}

int costoInsercion(char b) {
    return costo_insercion[b - 'a'];
}

int costoEliminacion(char a) {
    return costo_eliminacion[a - 'a'];
}

int costoTransposicion(char a, char b) {
    return costo_transposicion[a - 'a'][b - 'a'];
}

int ProgramacionDinamicaDistanciaMinima(const string &cadena1, const string &cadena2) {
    int m = cadena1.size();
    int n = cadena2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    //Bases DP
    for (int i = 0; i <= m; ++i) dp[i][0] = i > 0 ? dp[i - 1][0] + costoEliminacion(cadena1[i - 1]) : 0;
    for (int j = 0; j <= n; ++j) dp[0][j] = j > 0 ? dp[0][j - 1] + costoInsercion(cadena2[j - 1]) : 0;

    //Llenar la tabla de DP
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int costoSustituir = dp[i - 1][j - 1] + costoSubstitucion(cadena1[i - 1], cadena2[j - 1]);
            int costoInsertar = dp[i][j - 1] + costoInsercion(cadena2[j - 1]);
            int costoEliminar = dp[i - 1][j] + costoEliminacion(cadena1[i - 1]);

            dp[i][j] = min({costoSustituir, costoInsertar, costoEliminar});

            // Considerar transposición si es aplicable
            if (i > 1 && j > 1 && cadena1[i - 1] == cadena2[j - 2] && cadena1[i - 2] == cadena2[j - 1]) {
                dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + costoTransposicion(cadena1[i - 1], cadena1[i - 2]));
            }
        }
    }

    return dp[m][n];
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

    if (configuracion) {
        ifstream archivo("entrada.txt");
        if (!archivo.is_open()) {
            cerr << "Error al abrir el archivo." << endl;
            return EXIT_FAILURE;
        }

        int iteracion;
        int n;
        int m;
        archivo >> iteracion;
        string cadena1, cadena2;

        for (int i = 0; i < iteracion; ++i) {
            archivo >> cadena1 >> cadena2;

            m = cadena1.size();
            n = cadena2.size();

            auto inicio = chrono::high_resolution_clock::now();
            int resultado = ProgramacionDinamicaDistanciaMinima(cadena1, cadena2);
            auto fin = chrono::high_resolution_clock::now();

            chrono::duration<double> duracion = fin - inicio;

            cout << "S1: " << cadena1 << "\t" << "S2: " << cadena2 << endl;
            cout << "Distancia mínima de edición: " << resultado << endl;
            cout << "Tiempo de ejecución: " << duracion.count() * 1e9 << " nanosegundos" << endl;

            cout << "Memoria utilizada por la tabla de DP (aproximada): " << (m * n * sizeof(int)) / 1024.0 << " KB\n" << endl;
        }

        archivo.close();
    } else {
        string cadena1, cadena2;
        cout << "Ingrese la primera cadena: ";
        cin >> cadena1;
        cout << "Ingrese la segunda cadena: ";
        cin >> cadena2;

        auto inicio = chrono::high_resolution_clock::now();
        int resultado = ProgramacionDinamicaDistanciaMinima(cadena1, cadena2);
        auto fin = chrono::high_resolution_clock::now();

        chrono::duration<double> duracion = fin - inicio;
        cout << "Distancia mínima de edición: " << resultado << endl;
        cout << "Tiempo de ejecución: " << duracion.count() << " segundos" << endl;

        cout << "Memoria utilizada por la tabla de DP (aproximada): " << (cadena1.size() * cadena2.size() * sizeof(int)) / 1024.0 << " KB" << endl;
    }

    return 0;
}