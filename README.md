# Calculator
## Задание

Напишите программу калькулятора, который вычисляет значение выражения, заданного на очень простом языке целочисленных вычислений. Программа должна принимать выражение в качестве аргумента, вычислять значение выражения и печатать результат на консоль.

Пример:
```bash
$ calculator.exe "mult(2, 2)"
4
```
Ещё примеры выражений:

Ввод | Вывод
-----|------
`add(1, 2)` | `3`
`add(1, mult(2, 3))` | `7`
`mult(add(2, 2), div(9, 3))` | `12`
`let(a, 5, add(a, a))`|`10`
`let(a, 5, let(b, mult(a, 10), add(b, a)))`|`55`
`let(a, let(b, 10, add(b, b)), let(b, 20, add(a, b)))`|`40`

Состав выражения:
* Числа:
 **целые числа** в диапазоне `[numeric_limits<int>::min(), numeric_limits<int>::max()]`
* Переменные: 
 **строки символов**, символ из диапазона `[a-z, A-Z]`
* Арифметические функции: `add()`, `sub()`, `mult()`, `div()`.<br/> 
Каждая функция принимает два произвольных выражения в качестве аргументов. Другими словами, любой из аргументов может быть произвольным выражением из данного списка.
* Оператор `let` для присваивания значений переменным:
`let(<variable name>, <value>, <expression where variable is used>)`.<br/>
Так же, как и в случае с арифметическими функциями, выражение, где используется переменная, может быть **произвольным выражением** из данного списка.

Пожалуйста, отправьте то, что вы считаете *__тестируемым и поддерживаемым промышленным кодом__*.  Если формулировка задачи неясна, делайте предположения, но, пожалуйста, укажите свои предположения в комментариях к решению.
