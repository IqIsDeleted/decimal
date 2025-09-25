# Decimal Library

[![C](https://img.shields.io/badge/C-C11-blue)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
[![Standard](https://img.shields.io/badge/Standard-C%20Library%20Extension-brightgreen)](https://en.wikipedia.org/wiki/C_decimal_floating_point)
[![Tests](https://img.shields.io/badge/Tests-Check%20Framework-success)](https://libcheck.github.io/check/)

Реализация типа данных `decimal` на языке C, предоставляющая точные десятичные вычисления с фиксированной точкой. Библиотека полностью реализует арифметические, сравнительные и преобразовательные операции для работы с decimal-числами.

## О проекте

Проект представляет собой реализацию типа `s21_decimal`, аналогичного `decimal` в C#. Основные особенности:

- **Точные вычисления**: Исключает ошибки округления, характерные для бинарной арифметики с плавающей точкой
- **Полный набор операций**: Арифметика, сравнения, преобразования
- **Поддержка особых случаев**: Обработка NaN, бесконечностей, переполнений
- **Кроссплатформенность**: Написана на стандартном C11

## Архитектура

### Структура `s21_decimal`

```c
typedef struct {
    int bits[4];  // [0-2] - мантисса, [3] - знак и показатель степени
} s21_decimal;
```

### Структура проекта  

```text
src/
├── decimal/           # Основная библиотека
│   ├── arithmetic/    # Арифметические операции
│   ├── comparison/    # Операции сравнения
│   ├── conversion/    # Преобразования типов
│   └── other/         # Дополнительные функции
├── helpers/           # Вспомогательные функции
└── tests/             # Unit-тесты
```

## Быстрый запуск

### Предварительные требования  
- Компилятор ```gcc```
- Библиотека check для тестирования (если требуется).

#### Установка зависимостей
```bash
sudo apt update && sudo apt install build-essential libcheck-dev
```

## Сборка и использование

1. Клонирование репозитория:  
```bash
git clone https://github.com/IqIsDeleted/decimal.git
cd decimal
```

2. Сборка библиотеки:  
```bash
make decimal
```

3. Использование в проекте:  
Пример с использованием сложения и преобразования:  
``` C
#include "s21_decimal.h"

int main() {
    s21_decimal a = {{0}}, b = {{0}}, result = {{0}};
    
    // Инициализация значений
    s21_from_int_to_decimal(10, &a);
    s21_from_int_to_decimal(20, &b);
    
    s21_add(a, b, &result);
    
    int res_int;
    s21_from_decimal_to_int(result, &res_int);
    printf("Result: %d\n", res_int);
    
    return 0;
}
```  

4. Компиляция с библиотекой:
```bash
gcc -I./src your_program.c libs21_decimal.a -o your_program
```

## API

### Арифметические операции:
```C
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
```

### Операции сравнения
```C
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);
```

### Преобразования
```C
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
```

### Другие функции для работы с числами
```C
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
```

#### Коды возврата:
Все функции имеют код возврата:
- `0` - OK;
- `1` - число слишком велико или равно бесконечности;
- `2` - число слишком мало или равно отрицательной бесконечности;
- `3` - деление на 0.

## Команды Makefile  

| Команда | Назначение |
|---------|------------|
| `make all` | Сборка библиотеки и тестов |
| `make decimal` | Сборка основной библиотеки |
| `make test` | Запуск unit-тестов |
| `make gcov_report` | Генерация отчета о покрытии |
| `make clean` | Очистка временных файлов |
| `make rebuild` | Полная пересборка |

## Информация о проекте

- **Разработчик**: [IQisDeleted](https://github.com/IqIsDeleted)
- **Версия**: 1.0
- **Последнее обновление**: 05-2025