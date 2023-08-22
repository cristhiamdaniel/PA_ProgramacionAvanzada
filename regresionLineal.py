import numpy as np
import matplotlib.pyplot as plt

# Definición de datos iniciales
x = [1, 2, 3, 4, 5]
y = [2.2, 4.4, 5.5, 8.0, 10.5]

# Coeficientes propuestos para las rectas a evaluar
coefficients = [(2.02, 0.06), (2.0, 0.05), (2.5, 0.1), (2.1, 0.08)]

def calcular_ecm(y_real, y_pred):
    """
    Calcula el Error Cuadrático Medio (ECM) entre los valores reales y los predichos.
    """
    errores_cuadrados = []
    for yi, ypi in zip(y_real, y_pred):
        error = yi - ypi
        error_cuadrado = error**2
        errores_cuadrados.append(error_cuadrado)

    suma_errores_cuadrados = sum(errores_cuadrados)
    numero_datos = len(y_real)
    ecm = suma_errores_cuadrados / numero_datos

    return ecm

def graficar_recta(ax, x, m, b, ecm):
    """
    Grafica la recta definida por m y b en el eje dado.
    """
    x_line = np.linspace(min(x), max(x), 100)
    y_line = m * x_line + b
    ax.plot(x_line, y_line, label=f'y = {m}x + {b}\nECM = {ecm:.4f}')

def graficar_datos_errores(ax, x, y, y_pred):
    """
    Grafica los datos iniciales, puntos predichos y líneas de error en el eje dado.
    """
    ax.scatter(x, y, color='blue', label='Datos Iniciales')
    for xi, yi, ypi in zip(x, y, y_pred):
        ax.plot([xi, xi], [yi, ypi], color='gray', linestyle='--')
        ax.scatter(xi, ypi, color='green', marker='x', label='_nolegend_')

# Creación de subplots
fig, axs = plt.subplots(1, 4, figsize=(20, 5))

# Iteración a través de los coeficientes
for idx, (m, b) in enumerate(coefficients):
    ax = axs[idx]
    y_pred = [m*xi + b for xi in x]
    ecm = calcular_ecm(y, y_pred)
    graficar_recta(ax, x, m, b, ecm)
    graficar_datos_errores(ax, x, y, y_pred)
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.legend()

plt.tight_layout()
plt.show()
