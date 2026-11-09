import time

def generar_pascal(n: int):
    fila = [1]
    for i in range(1, n + 1):
        nueva = [1] * (i + 1)
        for j in range(1, i):
            nueva[j] = fila[j - 1] + fila[j]
        fila = nueva
    return fila

def mostrar_polinomio(c: list, n: int):
    print(f"Polinomio generado (x+1)^{n}:")
    for k in range(n + 1):
        grado = n - k
        if grado == 0:
            print(f"  + {c[k]}")
        elif grado == 1:
            print(f"  + {c[k]}x")
        else:
            print(f"  + {c[k]}x^{grado}")

def calcular_por_pasos(c: list, n: int, x):
    total = 0
    print(f"\n--- Calculo por pasos para n={n}, x={x} ---")
    for k in range(n + 1):
        grado = n - k
        termino = c[k] * (x ** grado)
        total += termino
        print(f"Paso {k + 1} (x^{grado}): termino = {termino}, acumulado = {total}")
    print(f"Resultado final f({x}) = {total} (Comprobacion directa: {(x + 1)**n})")

if __name__ == "__main__":
    print("=== PRUEBA DIAGNOSTICA - EJERCICIO 2 (PYTHON) ===\n")

    # a y b: Demostración con n = 4, x = 2
    n_demo = 4
    x_demo = 2
    c_demo = generar_pascal(n_demo)
    mostrar_polinomio(c_demo, n_demo)
    calcular_por_pasos(c_demo, n_demo, x_demo)

    # Medición del tiempo para generar n = 100
    inicio = time.perf_counter()
    c_100 = generar_pascal(100)
    fin = time.perf_counter()

    tiempo_ms = (fin - inicio) * 1000.0
    print(f"\nTiempo necesario para generar n=100 en Python: {tiempo_ms:.6f} ms")
