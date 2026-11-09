import time

def generar_pascal(n):
    # En Python las listas ya son estructuras de memoria dinámica
    fila = [1] * (n + 1)
    for i in range(1, n + 1):
        fila[i] = fila[i - 1] * (n - i + 1) // i
    return fila

def mostrar_polinomio(n, coef):
    terminos = []
    for i in range(n + 1):
        potencia = n - i
        c = coef[i]
        if potencia == 0:
            terminos.append(f"{c}")
        elif potencia == 1:
            terminos.append(f"{c if c != 1 else ''}x")
        else:
            terminos.append(f"{c if c != 1 else ''}x^{potencia}")
    print(f"\nPolinomio: (x+1)^{n} = " + " + ".join(terminos) + "\n")

def evaluar_polinomio(n, coef, x):
    print(f"Evaluando para x = {x} por pasos:")
    suma = 0
    for i in range(n + 1):
        termino = coef[i] * (x ** (n - i))
        suma += termino
        print(f"Paso {i+1}: termino {coef[i]} * ({x})^{n-i} = {termino} | Suma parcial = {suma}")
    print(f"Resultado final f({x}) = {suma}")

if __name__ == "__main__":
    n = int(input("Ingrese el grado del polinomio (n): "))
    x = float(input("Ingrese el valor de x: "))

    coeficientes = generar_pascal(n)
    mostrar_polinomio(n, coeficientes)
    evaluar_polinomio(n, coeficientes, x)

    # Requerimiento de medicion de tiempo para n=100
    print("\n--- PRUEBA DE RENDIMIENTO (n = 100) ---")
    inicio = time.time()
    # Iteramos las mismas 10,000 veces que en C para una comparacion justa
    for _ in range(10000): 
        _ = generar_pascal(100)
    fin = time.time()

    print(f"Tiempo para generar n=100 (10000 iteraciones en Python): {fin - inicio:.6f} segundos")