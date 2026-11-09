#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>
#include <cctype>

struct Casilla {
    int col; // 1 a 8 ('a'-'h')
    int fila; // 1 a 8 ('1'-'8')
    bool valida;
};

static Casilla validar_casilla(const std::string &s) {
    if (s.length() != 2) return {0, 0, false};
    char c = static_cast<char>(std::tolower(static_cast<unsigned char>(s[0])));
    char f = s[1];
    if (c < 'a' || c > 'h' || f < '1' || f > '8') return {0, 0, false};
    return {c - 'a' + 1, f - '0', true};
}

static bool es_salto_caballo(int c1, int f1, int c2, int f2) {
    int dc = std::abs(c2 - c1);
    int df = std::abs(f2 - f1);
    return (dc == 1 && df == 2) || (dc == 2 && df == 1);
}

static std::string verificar_movimientos(const std::string &ak, const std::string &cadena) {
    Casilla act = validar_casilla(ak);
    if (!act.valida) return "Incorrecto: Posición inicial inválida.";

    std::istringstream iss(cadena);
    std::string mov;
    int idx = 0;

    while (iss >> mov) {
        idx++;
        if (mov[0] != 'K') {
            return "movimiento INCORRECTO falla letra " + std::string(1, mov[0]) + " no pertenece a un caballo.";
        }
        Casilla dest = validar_casilla(mov.substr(1));
        if (!dest.valida || !es_salto_caballo(act.col, act.fila, dest.col, dest.fila)) {
            return "INCORRECTO falla en el movimiento " + std::to_string(idx) + ".";
        }
        act = dest;
    }
    return "movimiento CORRECTO.";
}

int main() {
    std::cout << "=== PRUEBA DIAGNOSTICA - EJERCICIO 1 ===\n\n";

    // Casos de ejemplo del PDF
    struct Caso { std::string ak; std::string c; };
    std::vector<Caso> casos = {
        {"a1", "Kc2 Kd4 Kb3 Kc5"},
        {"a1", "Kc2 Kd4 Kb4 Kc5"},
        {"a2", "Kc3 Ke4 Kf6 Ke8 Kg7"},
        {"a2", "Kc8 Ke4 Kf6 Ke8 Kg7"},
        {"a8", "Kb6 Kd7"},
        {"a8", "Kb6 Kb7"},
        {"a1", "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Kb4"},
        {"a1", "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4"},
        {"a1", "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kh6 Kb4"}
    };

    for (size_t i = 0; i < casos.size(); i++) {
        std::cout << "Para Ak = " << casos[i].ak << " y C= " << casos[i].c
                  << " salida: " << verificar_movimientos(casos[i].ak, casos[i].c) << "\n";
    }

    // Medicion de tiempo sobre los 500 movimientos oficiales
    std::ifstream f("movimientos_500.txt");
    if (!f.is_open()) {
        f.open("ejercicio_1/movimientos_500.txt");
    }
    if (!f.is_open()) {
        f.open("PRUEBA_DIAGNOSTICA/2_Josnaiker_Rivas/ejercicio_1/movimientos_500.txt");
    }

    if (!f.is_open()) {
        std::cout << "\nNo se pudo abrir movimientos_500.txt\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << f.rdbuf();
    std::string movs_500 = buffer.str();
    f.close();

    std::cout << "\n=== Resultado 500 movimientos ===\n\n";
    std::cout << verificar_movimientos("a2", movs_500) << "\n";

    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; i++) {
        verificar_movimientos("a2", movs_500);
    }
    auto t2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> ms = t2 - t1;
    std::cout << "Tiempo en verificar 10 veces los 500 movimientos: " << ms.count() << " ms\n";

    return 0;
}
