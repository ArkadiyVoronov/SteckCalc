// Файл "streal.h"
// Стек вещественных чисел, интерфейс
//
#ifndef ST_REAL_H
#define ST_REAL_H

// Прототипы функций, реализующих предписания стека:

void st_init(int maxSize); // Начать работу (вх: цел
                           //     макс. размер стека)
void st_terminate();    // Закончить работу
void st_push(double x); // Добавить эл-т (вх: вещ x)
double st_pop();        // Взять элемент: вещ
double st_top();        // Вершина стека: вещ
int st_size();          // Текущий размер стека: цел
bool st_empty();        // Стек пуст? : лог
int st_maxSize();       // Макс. размер стека: цел
bool st_freeSpace();    // Есть свободное место? : лог
void st_clear();        // Удалить все элементы
double st_elementAt(int i); // Элемент стека на
                            //   глубине (вх: i): вещ
#endif
// Конец файла "streal.h"
