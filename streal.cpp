// Файл "stcalc.cpp"
// Реализация стекового калькулятора на базе стека
//
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "streal.h" // Интерфейс исполнителя "стек"

// Прототипы функций, реализующих команды калькулятора:
// Арифметические операции
static void onAdd();
static void onSub();
static void onMul();
static void onDiv();

// Добавить число в стек(вх: текстовая запись числа)
static void onPush(const char* line);

// Вычисление математических функций
static void onSin();     // sin
static void onCos();     // cos
static void onExp();     // Экспонента
static void onLog();     // Натуральный логарифм
static void onSqrt();    // Квадратный корень

// Другие команды
static void onPop();     // Удалить вершину стека
static void onClear();   // Очистить стек
static void display();   // Напечатать вершину стека
static void onShow();    // Напечатать содержимое стека
static void printHelp(); // Напечатать подсказку

int main() {
    char line[256]; // Буфер для ввода строки
    int linelen;    // Длина строки

    st_init(1024);  // Стек.начать работу(1024)
                    //   1024 — макс. глубина стека
    printHelp();    // Напечатать подсказку

    while (true) {          // Цикл до бесконечности
        scanf("%s", line);      // ввести строку
        linelen = strlen(line); // длина строки
        if (linelen == 0)
            continue;

        // Разобрать команду и вызвать реализующую
        // ее функцию
        if (strcmp(line, "+") == 0) {
            onAdd();
        } else if (strcmp(line, "-") == 0) {
            onSub();
        } else if (strcmp(line, "*") == 0) {
            onMul();
        } else if (strcmp(line, "/") == 0) {
            onDiv();
        } else if (strcmp(line, "sin") == 0) {
            onSin();
        } else if (strcmp(line, "cos") == 0) {
            onCos();
        } else if (strcmp(line, "exp") == 0) {
            onExp();
        } else if (strcmp(line, "log") == 0) {
            onLog();
        } else if (strcmp(line, "sqrt") == 0) {
            onSqrt();
        } else if (strcmp(line, "=") == 0) {
            display();
        } else if (         // Если это число
            isdigit(line[0]) || (
                linelen > 1 &&
                (line[0] == '-' || line[0] == '+') &&
                isdigit(line[1])
            )
        ) {
            onPush(line);   // Добавить число в стек
        } else if (strcmp(line, "pop") == 0) {
            onPop();
        } else if (strcmp(line, "clear") == 0) {
            onClear();
        } else if (strcmp(line, "show") == 0) {
            onShow();
        } else if (strcmp(line, "quit") == 0) {
            break;       // Завершить работу
        } else {         // Неправильная команда =>
            printHelp(); //     напечатать подсказку
        }
    }
    return 0;
}

static void onAdd() {
    double y, x;
    if (st_size() < 2) {
        printf("Stack depth < 2.\n");
        return;
    }
    y = st_pop();
    x = st_pop();
    st_push(x + y);
    display();
}

static void onSub() {
    double y, x;
    if (st_size() < 2) {
        printf("Stack depth < 2.\n");
        return;
    }
    y = st_pop();
    x = st_pop();
    st_push(x - y);
    display();
}

static void onMul() {
    double y, x;
    if (st_size() < 2) {
        printf("Stack depth < 2.\n");
        return;
    }
    y = st_pop();
    x = st_pop();
    st_push(x * y);
    display();
}

static void onDiv() {
    double y, x;
    if (st_size() < 2) {
        printf("Stack depth < 2.\n");
        return;
    }
    y = st_pop();
    x = st_pop();
    st_push(x / y);
    display();
}

static void onPush(const char* line) {
    double x = atof(line);
    st_push(x);
}

static void onSin() {
    double x;
    if (st_empty()) {
        printf("Stack empty.\n");
        return;
    }
    x = st_pop();
    st_push(sin(x));
    display();
}

static void onCos() {
    double x;
    if (st_empty()) {
        printf("Stack empty.\n");
        return;
    }
    x = st_pop();
    st_push(cos(x));
    display();
}

static void onExp() {
    double x;
    if (st_empty()) {
        printf("Stack empty.\n");
        return;
    }
    x = st_pop();
    st_push(exp(x));
    display();
}

static void onLog() {
    double x;
    if (st_empty()) {
        printf("Stack empty.\n");
        return;
    }
    x = st_pop();
    st_push(log(x));
    display();
}

static void onSqrt() {
    double x;
    if (st_empty()) {
        printf("Stack empty.\n");
        return;
    }
    if (st_top() < 0.0) {
        printf("Arg. of square root is negative.\n");
        return;
    }
    x = st_pop();
    st_push(sqrt(x));
    display();
}

static void onPop() {
    st_pop();
}

static void onClear() {
    st_clear();
}

static void display() {
    if (!st_empty()) {
        printf("=%lf\n", st_top());
    } else {
        printf("stack empty\n");
    }
}

static void onShow() {
    int d = st_size();
    printf("Depth of stack = %d.", d);
    if (d > 0)
        printf(" Stack elements:\n");
    else
        printf("\n");

    for (int i = 0; i < d; i++) {
        printf("  %lf\n", st_elementAt(i));
    }
}

static void printHelp() {
    printf(
        "Stack Calculator commands:\n"
        "    <number>    Push а number in stack\n"
        "    +, -, *, /  Ariphmetic operations\n"
        "    sin, cos,   Calculate a function\n"
        "    exp, log,   \n"
        "    sqrt        \n"
        "    =           Display the stack top\n"
        "    pop         Remove the stack top\n"
        "    show        Show the stack\n"
        "    clear       Clear the stack\n"
        "    quit        Terminate the program\n"
    );
}
// Конец файла "stcalc.cpp"
