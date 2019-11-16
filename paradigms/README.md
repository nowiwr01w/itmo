## [Домашнее задание 4. Функциональные выражения на JavaScript](https://github.com/nowiwr01/itmo/tree/master/paradigms/hw4)

Модификации
 * *Базовая*
    * Код должен находиться в файле `functionalExpression.js`.
    * [Исходный код тестов](tests/javascript/jstest/functional/FunctionalExpressionTest.java)
        * Запускать c аргументом `hard` или `easy`;
 * *IffAbs*. Дополнительно реализовать поддержку:
    * переменных: `y`, `z`;
    * операций:
        * `abs` – абсолютное значение, `-2 abs` равно 2;
        * `iff` – условный выбор:
            если первый аргумент неотрицательный,
            вернуть второй аргумент,
            иначе вернуть третий аргумент:
            * `iff 1 2 3` равно 2
            * `iff -1 -2 -3` равно -3
            * `iff 0 1 2` равно 1;
    * [Исходный код тестов](tests/javascript/jstest/functional/FunctionalIffAbsTest.java)
        * Запускать c аргументом `hard`

## [Домашнее задание 5. Объектные выражения на JavaScript](https://github.com/nowiwr01/itmo/tree/master/paradigms/hw5)

Модификации
 * *Базовая*
    * Код должен находиться в файле `objectExpression.js`.
    * [Исходный код тестов](tests/javascript/jstest/object/ObjectExpressionTest.java)
        * Запускать c аргументом `easy`, `hard` или `bonus`.
 * *ArcTan*. Дополнительно реализовать поддержку:
    * функций:
        * `ArcTan` (`atan`) – арктангенс, `1256 atan` примерно равно 1.57;
        * `ArcTan2` (`atan2`) – арктангенс, `841 540 atan2` примерно равно 1;
    * [Исходный код тестов](tests/javascript/jstest/object/ObjectArcTanTest.java)
 * *SinhCosh*. Дополнительно реализовать поддержку:
    * унарных функций:
        * `Sinh` (`sinh`) – гиперболический синус, `3 sinh` немного больше 10;
        * `Cosh` (`cosh`) – гиперболический косинус, `3 cosh` немного меньше 10;
    * [Исходный код тестов](tests/javascript/jstest/object/ObjectSinhCoshTest.java)

## [Домашнее задание 6. Обработка ошибок на JavaScript](https://github.com/nowiwr01/itmo/tree/master/paradigms/hw6)

Модификации
 * *Базовая*
    * Код должен находиться в файле `objectExpression.js`.
    * [Исходный код тестов](tests/javascript/jstest/prefix/PrefixParserTest.java)
        * Запускать c аргументом `easy` или `hard`
 * *PrefixSumexpSoftmax*. Дополнительно реализовать поддержку:
    * операций произвольного числа аргументов:
        * `Sumexp` (`sumexp`) – сумма экспонент, `(8 8 9)` примерно равно 14065;
        * `Softmax` (`softmax`) – softmax первого аргумента, `(softmax 1 2 3)` примерно равно 9;
    * [Исходный код тестов](tests/javascript/jstest/prefix/PrefixSumexpSoftmaxTest.java)
    
## [Домашнее задание 7. Линейная алгебра на Clojure](https://github.com/nowiwr01/itmo/tree/master/paradigms/hw7)

Модификации
 * *Базовая*
    * Код должен находиться в файле `linear.clj`.
    * Исходный код тестов
        * [Простой вариант](tests/clojure/cljtest/linear/LinearBinaryTest.java)
        * [Сложный вариант](tests/clojure/cljtest/linear/LinearNaryTest.java)
 * *Shapeless*
    * Добавьте операции поэлементного сложения (`s+`),
        вычитания (`s-`) и умножения (`s*`) чисел и
        векторов любой (в том числе, переменной) формы.
        Например, `(s+ [[1 2] 3] [[4 5] 6])` должно быть равно `[[5 7] 9]`.
    * [Исходный код тестов](tests/clojure/cljtest/linear/LinearShapelessTest.java)
    
## [Домашнее задание 8. Функциональные выражения на Clojure](https://github.com/nowiwr01/itmo/tree/master/paradigms/hw8)

Модификации
 * *Базовая*
    * Код должен находиться в файле `expression.clj`.
    * [Исходный код тестов](tests/clojure/cljtest/functional/ClojureFunctionalExpressionTest.java)
        * Запускать c аргументом `easy` или `hard`
 * *SquareSqrt*. Дополнительно реализовать поддержку:
    * унарных операций:
        * `square` (`square`) – возведение в квадрат, `(square 3)` равно 9;
        * `sqrt` (`sqrt`) – извлечение квадратного корня из модуля аргумента, `(sqrt -9)` равно 3.
    * [Исходный код тестов](tests/clojure/cljtest/functional/ClojureFunctionalSquareSqrtTest.java)
 * *MinMax*. Дополнительно реализовать поддержку:
    * операций:
        * `min` (`min`) – минимум, `(min 1 2 6)` равно 1;
        * `max` (`max`) – максимум, `(min 1 2 6)` равно 6;
    * [Исходный код тестов](tests/clojure/cljtest/functional/ClojureFunctionalMinMaxTest.java)
 * *MedAvg*. Дополнительно реализовать поддержку:
    * операций:
        * `med` (`med`) – медиана, `(med 1 2 6)` равно 2;
        * `avg` (`max`) – среднее, `(min 1 2 6)` равно 3;
    * [Исходный код тестов](tests/clojure/cljtest/functional/ClojureFunctionalMedAvgTest.java)
    
## [Домашнее задание 9. Объектные выражения на Clojure](https://github.com/nowiwr01/itmo/tree/master/paradigms/hw9)

Модификации
 * *Базовая*
    * Код должен находиться в файле `expression.clj`.
    * [Исходный код тестов](tests/clojure/cljtest/object/ClojureObjectExpressionTest.java)
        * Запускать c аргументом `easy` или `hard`
 * *SinhCosh*. Дополнительно реализовать поддержку:
    * унарных операций:
        * `Sinh` (`sinh`) – гиперболический синус, `(sinh 3)` немного больше 10;
        * `Cosh` (`cosh`) – гиперболический косинус, `(cosh 3)` немного меньше 10.
    * [Исходный код тестов](tests/clojure/cljtest/object/ClojureObjectSinhCoshTest.java)

## [Домашнее задание 11. Ассоциативные массивы на Prolog](https://github.com/nowiwr01/itmo/tree/master/paradigms/hw11)

Модификации
 * *Простая*
    * Код должен находиться в файле `sorted-list-map.pl`.
    * [Исходный код тестов](tests/prolog/prtest/list/PrologListTest.java)
        * Запускать c аргументом `sorted`
 * *Сложная*
    * Код должен находиться в файле `tree-map.pl`.
    * [Исходный код тестов](tests/prolog/prtest/tree/PrologTreeTest.java)
        * Запускать c аргументом `hard` или `bonus`
 * *Replace*
    * Добавьте правило `map_replace(Map, Key, Value, Result)`,
        заменяющего значения ключа на указанное, если ключ присутствует.
    * Исходный код тестов:
        [сложные](tests/prolog/prtest/tree/PrologTreeReplaceTest.java)
 * *Size*
    * Добавьте правило `map_size(Map, Size)`, возвращающее размер дерева
    * Исходный код тестов:
        [сложные](tests/prolog/prtest/tree/PrologTreeSizeTest.java)
 * *floorKey*
    * Добавьте правило `map_floorKey(Map, Key, FloorKey)`,
      вовзращающее максимальный ключ, меньший либо равный заданному.
    * Исходный код тестов:
        [простые](tests/prolog/prtest/list/PrologListFloorTest.java)

## Исходный код к лекциям по JavaScript

[Скрипт с примерами](tests/javascript/examples.js)

Запуск примеров
 * [В браузере](tests/javascript/RunJS.html)
 * Из консоли
    * [на Java](tests/javascript/RunJS.java): [RunJS.cmd](tests/javascript/RunJS.cmd), [RunJS.sh](tests/javascript/RunJS.sh)
    * [на node.js](tests/javascript/RunJS.node.js): `node RunJS.node.js`

Лекция 1. Типы и функции
 * [Типы](tests/javascript/examples/1_1_types.js)
 * [Функции](tests/javascript/examples/1_2_functions.js)
 * [Функции высшего порядка](tests/javascript/examples/1_3_functions-hi.js).
   Обратите внимание на реализацию функции `mCurry`.

Лекция 2. Объекты и методы
 * [Объекты](tests/javascript/examples/2_1_objects.js)
 * [Замыкания](tests/javascript/examples/2_2_closures.js)
 * [Модули](tests/javascript/examples/2_3_modules.js)
 * [Пример: стеки](tests/javascript/examples/2_4_stacks.js)

Лекция 3. Другие возможности
 * [Обработка ошибок](tests/javascript/examples/3_1_errors.js)
 * [Чего нет в JS](tests/javascript/examples/3_2_no.js)
 * [Стандартная библиотека](tests/javascript/examples/3_3_builtins.js)
 * [Работа со свойствами](tests/javascript/examples/3_4_properties.js)
 * [JS 6+](tests/javascript/examples/3_5_js6.js)

## Исходный код к лекциям по Clojure

Запуск Clojure
 * Консоль: [Windows](tests/clojure/RunClojure.cmd), [*nix](tests/clojure/RunClojure.sh)
    * Интерактивный: `RunClojure`
    * С выражением: `RunClojure --eval "<выражение>"`
    * Скрипт: `RunClojure <файл скрипта>`
    * Справка: `RunClojure --help`
 * IDE
    * IntelliJ Idea: [плагин Cursive](https://cursive-ide.com/userguide/)

[Скрипт со всеми примерами](tests/clojure/examples.clj)

Лекция 1. Функции
 * [Введение](tests/clojure/examples/1_1_intro.clj)
 * [Функции](tests/clojure/examples/1_2_functions.clj)
 * [Списки](tests/clojure/examples/1_3_lists.clj)
 * [Вектора](tests/clojure/examples/1_4_vectors.clj)
 * [Функции высшего порядка](tests/clojure/examples/1_5_functions-2.clj)

Лекция 2. Внешний мир
 * [Ввод-вывод](tests/clojure/examples/2_1_io.clj)
 * [Разбор и гомоиконность](tests/clojure/examples/2_2_read.clj)
 * [Порядки вычислений](tests/clojure/examples/2_3_evaluation-orders.clj)
 * [Потоки](tests/clojure/examples/2_4_streams.clj)
 * [Отображения и множества](tests/clojure/examples/2_5_maps.clj)

Лекция 3. Объекты и вычисления
 * [Прототипное наследование](tests/clojure/examples/3_1_js-objects.clj)
 * [Классы](tests/clojure/examples/3_2_java-objects.clj)
 * [Изменяемое состояние](tests/clojure/examples/3_3_mutable-state.clj)
 * [Числа Чёрча](tests/clojure/examples/3_4_church.clj)

Лекция 4. Комбинаторные парсеры
 * [Базовые функции](tests/clojure/examples/4_1_base.clj)
 * [Комбинаторы](tests/clojure/examples/4_2_combinators.clj)
 * [JSON](tests/clojure/examples/4_3_json.clj)
 * [Макросы](tests/clojure/examples/4_4_macro.clj)

## Исходный код к лекциям по Prolog

Запуск Prolog
 * [Windows](tests/prolog/RunProlog.cmd)
 * [*nix](tests/prolog/RunProlog.sh)

Лекция 1. Введение в пролог
 * [Учебный план](tests/prolog/examples/1_plan.pl)
 * [Вычисления](tests/prolog/examples/2_calc.pl)
 * [Списки](tests/prolog/examples/3_lists.pl)
 * [Задача о расстановке ферзей](tests/prolog/examples/4_queens.pl)
 * [Загадка Эйнштейна](tests/prolog/examples/5_einstein.pl)
 * [Арифметические выражения](tests/prolog/examples/6_expressions.pl)
