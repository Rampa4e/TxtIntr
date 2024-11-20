#include <iostream>
#include <cmath>
#include <string>
#include <stdexcept>

void print_help() {
    std::cout << "Тригонометрический калькулятор\n"
              << "Использование:\n"
              << "  calc -o <operation> -m <mode> <operand>\n\n"
              << "Параметры:\n"
              << "  -o, --operation   Операция: sin (синус) или cos (косинус).\n"
              << "  -m, --mode        Режим: degrees (градусы) или radians (радианы).\n"
              << "  <operand>         Число, для которого выполняется операция.\n"
              << "Пример:\n"
              << "  calc -o sin -m degrees 90\n";
}

double to_radians(double degrees) {
    return degrees * M_PI / 180.0;
}

int main(int argc, char* argv[]) {
    // Если программа запущена без параметров, выводим справку
    if (argc == 1) {
        print_help();
        return 0;
    }

    // Проверка минимального количества аргументов
    if (argc != 6) { // Должно быть 5 аргументов + имя программы
        std::cerr << "Ошибка: неверное количество аргументов.\n";
        print_help();
        return 1;
    }

    // Инициализация переменных
    std::string operation;
    std::string mode;
    double operand = 0.0;

    try {
        // Разбор аргументов
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if ((arg == "-o" || arg == "--operation") && i + 1 < argc) {
                operation = argv[++i];
            } else if ((arg == "-m" || arg == "--mode") && i + 1 < argc) {
                mode = argv[++i];
            } else if (i == argc - 1) { // Последний аргумент должен быть операндом
                operand = std::stod(argv[i]);
            }
        }

        // Проверка значений параметров
        if (operation != "sin" && operation != "cos") {
            throw std::invalid_argument("Недопустимая операция. Используйте sin или cos.");
        }
        if (mode != "degrees" && mode != "radians") {
            throw std::invalid_argument("Недопустимый режим. Используйте degrees или radians.");
        }

        // Преобразование в радианы, если режим - градусы
        if (mode == "degrees") {
            operand = to_radians(operand);
        }

        // Вычисление результата
        double result = 0.0;
        if (operation == "sin") {
            result = std::sin(operand);
        } else if (operation == "cos") {
            result = std::cos(operand);
        }

        // Вывод результата
        std::cout << "Результат " << operation << "(" << argv[argc - 1] << "): " << result << std::endl;

    } catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        print_help();
        return 1;
    }

    return 0;
}



