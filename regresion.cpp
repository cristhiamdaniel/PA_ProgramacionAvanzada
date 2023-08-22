//
// Created by cristhiamdaniel on 21/08/23.
//

#include <iostream>
#include <fstream>

using namespace std;

// 1. Cálculo de Pendiente y Ordenada al Origen
void calcularRegresion(double* x, double* y, int n, double &m, double &b) {
    double sumX = 0, sumY = 0, sumX2 = 0, sumXY = 0;
    for (int i = 0; i < n; i++) {
        sumX += x[i];
        sumY += y[i];
        sumX2 += x[i] * x[i];
        sumXY += x[i] * y[i];
    }

    m = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    b = (sumY - m * sumX) / n;
}

// 2. Lectura de Datos desde Archivo
int leerDatosDesdeArchivo(const char* nombreArchivo, double*& x, double*& y) {
    ifstream file(nombreArchivo);
    int n;
    file >> n;
    x = new double[n];
    y = new double[n];

    for (int i = 0; i < n; i++) {
        file >> x[i] >> y[i];
    }

    file.close();
    return n;
}

// 3. Predicción de Valores
double predecirY(double* m, double* b, double x) {
    return (*m) * x + (*b);
}

// 5. Escritura de Resultados en Archivo
void escribirResultadosEnArchivo(const char* nombreArchivo, double* m, double* b, double* x, double* y_pred, int n) {
    ofstream file(nombreArchivo);

    file << "x\tPrediccion\n";
    for (int i = 0; i < n; i++) {
        file << x[i] << "\t" << y_pred[i] << "\n";
    }

    file << "\nCoeficientes de Regresion:\n";
    file << "Pendiente (m): " << *m << "\n";
    file << "Ordenada al origen (b): " << *b << "\n";

    file.close();
}

int main() {
    // Suponiendo un archivo 'datos.txt' con el siguiente formato:
    // n (cantidad de datos)
    // x1 y1
    // x2 y2
    // ...
    // xn yn
    double* x;
    double* y;
    int n = leerDatosDesdeArchivo("/home/cristhiamdaniel/CLionProjects/PUJ_PA_202302/Semana6/datos.txt", x, y);

    double m, b;
    calcularRegresion(x, y, n, m, b);

    double* y_pred = new double[n];
    for (int i = 0; i < n; i++) {
        y_pred[i] = predecirY(&m, &b, x[i]);
    }

    escribirResultadosEnArchivo("resultados.txt", &m, &b, x, y_pred, n);

    delete[] x;
    delete[] y;
    delete[] y_pred;

    return 0;
}
