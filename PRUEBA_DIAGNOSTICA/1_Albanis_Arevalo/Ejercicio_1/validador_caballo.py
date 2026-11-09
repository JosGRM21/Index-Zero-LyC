import os
import time

def parse_casilla(casilla):
    s = casilla.strip().lower()
    if len(s) == 2 and 'a' <= s[0] <= 'h' and '1' <= s[1] <= '8':
        return ord(s[0]) - ord('a'), ord(s[1]) - ord('1')
    return None

def es_salto_valido(origen, destino):
    dx = abs(destino[0] - origen[0])
    dy = abs(destino[1] - origen[1])
    return (dx == 1 and dy == 2) or (dx == 2 and dy == 1)

def validar_movimientos(ak, cadena, n=None):
    pos = parse_casilla(ak)
    if not pos:
        return f"INCORRECTO posicion inicial {ak} invalida."

    movs = cadena.strip().split()
    if n is not None:
        movs = movs[:n]

    for i, m in enumerate(movs, start=1):
        if not m.startswith('K'):
            return f"movimiento INCORRECTO falla letra {m[0]} no pertenece a un caballo."
        
        destino = parse_casilla(m[1:])
        if not destino or not es_salto_valido(pos, destino):
            return f"INCORRECTO falla en el movimiento {i}."
        pos = destino

    return "movimiento CORRECTO."

if __name__ == "__main__":
    casos = [
        ("a1", 4, "Kc2 Kd4 Kb3 Kc5"),
        ("a1", 4, "Kc2 Kd4 Kb4 Kc5"),
        ("a2", 5, "Kc3 Ke4 Kf6 Ke8 Kg7"),
        ("a2", 5, "Kc8 Ke4 Kf6 Ke8 Kg7"),
        ("a8", 2, "Kb6 Kd7"),
        ("a8", 2, "Kb6 Kb7"),
        ("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Kb4"),
        ("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4"),
        ("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kh6 Kb4"),
    ]

    print("--- CASOS DE PRUEBA ---")
    for ak, n, c in casos:
        print(f"Ak={ak} n={n} | C={c} -> salida: {validar_movimientos(ak, c, n)}")

    # Medir 10 veces los 500 movimientos
    ruta_500 = os.path.join(os.path.dirname(__file__), "movimientos_500.txt")
    if os.path.exists(ruta_500):
        with open(ruta_500, "r", encoding="utf-8") as f:
            c_500 = f.read().strip()
        
        t0 = time.perf_counter()
        for _ in range(10):
            res_500 = validar_movimientos("a2", c_500)
        t_total = time.perf_counter() - t0

        print("\n--- BENCHMARK 500 MOVIMIENTOS ---")
        print(f"Salida: {res_500}")
        print(f"Tiempo en verificar 10 veces: {t_total * 1000:.3f} ms (promedio: {t_total / 10 * 1000:.3f} ms)")
