import sys
import time

def pascal(n):
    t = [[1]]
    for i in range(1, n + 1):
        ant = t[i - 1]
        t.append([1] + [ant[j - 1] + ant[j] for j in range(1, i)] + [1])
    return t

def mostrar_polinomio(coefs):
    n = len(coefs) - 1
    terminos = []
    for i, c in enumerate(coefs):
        exp = n - i
        if exp == 0: terminos.append(str(c))
        elif exp == 1: terminos.append(f"{c}x" if c != 1 else "x")
        else: terminos.append(f"{c}x^{exp}" if c != 1 else f"x^{exp}")
    print(f"(x+1)^{n} = " + " + ".join(terminos))

def evaluar_por_pasos(coefs, x):
    n = len(coefs) - 1
    print(f"\n--- Calculo por pasos para f({x}) = ({x}+1)^{n} ---")
    total = 0
    for i, c in enumerate(coefs):
        exp = n - i
        termino = c * (x ** exp)
        total += termino
        print(f"Paso {i+1}: {c} * ({x})^{exp} = {termino}")
    print(f"Resultado f({x}) = {total}")

if __name__ == "__main__":
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 100
    x = int(sys.argv[2]) if len(sys.argv) > 2 else 2
    t = pascal(n)
    
    # a) Generar coeficientes y mostrar polinomio
    mostrar_polinomio(t[n])
    
    # b) Mostrar por pasos el cálculo para x dado
    evaluar_por_pasos(t[n], x)
    
    # Medir tiempo para n = 100
    t0 = time.perf_counter()
    pascal(100)
    t1 = time.perf_counter()
    print(f"\nTiempo en Python para n=100: {(t1 - t0)*1e6:.2f} us")
