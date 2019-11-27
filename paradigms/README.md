## [Домашнее задание 4. Функциональные выражения на JavaScript](https://github.com/nowiwr01/itmo/tree/master/paradigms/hw4)
 
   * Разработайте функции cnst, variable, add, subtract, multiply, divide, negate для вычисления выражений с одной переменной.
Функции должны позволять производить вычисления вида:

      ```
      let expr = subtract(
          multiply(
              cnst(2),
              variable("x")
          ),
          cnst(3)
      );
      println(expr(5));
      ```
   * При вычислении такого выражения вместо каждой переменной подставляется значение, переданное в качестве параметра функции expr (на данном этапе имена переменных игнорируются). Таким образом, результатом вычисления приведенного примера должно стать число 7
   * Тестовая программа должна вычислять выражение x2−2x+1, для x от 0 до 10
   * **Усложненный вариант.** Требуется написать функцию parse, осуществляющую разбор выражений, записанных в обратной польской записи. Например, результатом parse("x x 2 - * x * 1 +")(5) должно быть число 76
   * При выполнение задания следует обратить внимание на:
      * Применение функций высшего порядка
      * Выделение общего кода для бинарных операций
 
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
### Задание 1
* Разработайте классы Const, Variable, Add, Subtract, Multiply, Divide, Negate для представления выражений с одной переменной.
Пример описания выражения 2x-3:
   ```
   let expr = new Subtract(
       new Multiply(
           new Const(2),
           new Variable("x")
       ),
       new Const(3)
   );
   ```
* Метод evaluate(x) должен производить вычисления вида: При вычислении такого выражения вместо каждой переменной подставляется значение x, переданное в качестве параметра функции evaluate (на данном этапе имена переменных игнорируются). Таким образом, результатом вычисления приведенного примера должно стать число 7.
* Метод toString() должен выдавать запись выражения в обратной польской записи. Например, expr.toString() должен выдавать 2 x * 3 -.
 
### Задание 2. **Усложненный вариант.**
 * Метод diff("x") должен возвращать выражение, представляющее производную исходного выражения по переменной x. Например, expr.diff("x") должен возвращать выражение, эквивалентное new Const(2)
 * Выражения `new Subtract(new Const(2), new Const(0))` и
   ```
   new Subtract(
       new Add(
           new Multiply(new Const(0), new Variable("x")),
           new Multiply(new Const(2), new Const(1))
       )
       new Const(0)
   )
   ```              
так же будут считаться правильным ответом).
 
 * Функция parse должна выдавать разобранное объектное выражение.
 
### Задание 3. ***Бонусный вариант.***
 * Требуется написать метод simplify(), производящий вычисления константных выражений.
 
 Например, `parse("x x 2 - * 1 *").diff("x").simplify().toString()` должно возвращать `x x 2 - +`.
 * При выполнение задания следует обратить внимание на:
    * Применение инкапсуляции.
    * Выделение общего кода для операций.
 
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
 
  * Добавьте в предыдущее домашнее задание функцию parsePrefix(string), разбирающую выражения, задаваемые записью вида `(- (* 2 x) 3).` Если разбираемое выражение некорректно, метод parsePrefix должен бросать человеко-читаемое сообщение об ошибке.
  * Добавьте в предыдущее домашнее задание метод prefix(), выдающий выражение в формате, ожидаемом функцией parsePrefix.
  * При выполнение задания следует обратить внимание на:
    * Применение инкапсуляции.
    * Выделение общего кода для бинарных операций.
    * Обработку ошибок.
    * Минимизацию необходимой памяти.
 
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
 
  * **1.** Разработайте функции для работы с объектами линейной алгебры, которые представляются следующим образом:
    * скаляры – числа
    * векторы – векторы чисел;
    * матрицы – векторы векторов чисел.
  * **2.** Функции над векторами:
    * v+/v-/v* – покоординатное сложение/вычитание/умножение;
    * scalar/vect – скалярное/векторное произведение;
    * v*s – умножение на скаляр.
  * **3.** Функции над матрицами:
    * m+/m-/m* – поэлементное сложение/вычитание/умножение;
    * m*s – умножение на скаляр;
    * m*v – умножение на вектор;
    * m*m – матричное умножение;
    * transpose – траспонирование;
  * **4. Усложненный вариант.**
    * Ко всем функциям должны быть указаны контракты. Например, нельзя складывать вектора разной длины.
    * Все функции должны поддерживать произвольное число аргументов. Например (v+ [1 2] [3 4] [5 6]) должно быть равно [9 12].
  * **5.** При выполнение задания следует обратить внимание на:
       * Применение функций высшего порядка.
       * Выделение общего кода для операций.
 
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
 
  * **1.** Разработайте функции constant, variable, add, subtract, multiply и divide для представления арифметических выражений.
  
    * Пример описания выражения 2x-3:
         ```
         (def expr
           (subtract
             (multiply
               (constant 2)
               (variable "x"))
             (constant 3)))
         ```
    * Выражение должно быть функцией, возвращающей значение выражение при подстановке элементов, заданных отображением. Например, `(expr {"x" 2})` должно быть равно 1.
  * **2.** Разработайте разборщик выражений, читающий выражения в стандартной для Clojure форме. Например, `(parseFunction "(- (* 2 x) 3)")` должно быть эквивалентно expr.
  * **3. Усложненный вариант.** Функции add, subtract, multiply и divide должны принимать произвольное число аргументов. Разборщик так же должен допускать произвольное число аргументов для +, -, *.
  * **4.** При выполнение задания следует обратить внимание на:
    * Выделение общего кода для операций. 
 
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
 
  * **1.** Разработайте конструкторы Constant, Variable, Add, Subtract, Multiply и Divide для представления выражений с одной переменной.
    * Пример описания выражения 2x-3:
         ```
         (def expr
           (Subtract
             (Multiply
               (Constant 2)
               (Variable "x"))
             (Const 3)))
         ```                    
  * **2.** Функция (evaluate expression vars) должна производить вычисление выражения expression для значений переменных, заданных отображением vars. Например, `(evaluate expr {"x" 2})` должно быть равно 1.
  * **3.** Функция (toString expression) должна выдавать запись выражения в стандартной для Clojure форме.
  * **4.** Функция (parseObject "expression") должна разбирать выражения, записанные в стандартной для Clojure форме. Например,
`(parseObject "(- (* 2 x) 3)")` должно быть эквивалентно expr.
  * **5.** Функция (diff expression "variable") должена возвращать выражение, представляющее производную исходного выражения по заданой пермененной. Например, `(diff expression "x")` должен возвращать выражение, эквивалентное `(Constant 2)`, при этом выражения `(Subtract (Const 2) (Const 0))` и
      ```
      (Subtract
        (Add
          (Multiply (Const 0) (Variable "x"))
          (Multiply (Const 2) (Const 1)))
        (Const 0))
      ```                    
так же будут считаться правильным ответом.
  * **6. Усложненный вариант.** Констуркторы Add, Subtract, Multiply и Divide должны принимать произвольное число аргументов. Разборщик так же должен допускать произвольное число аргументов для +, -, *, /.
  * **7.** При выполнение задания можно использовать любой способ преставления объектов.

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
 
  * **1.** Реализуйте ассоциативный массив (map).
  * **2. Простой вариант.** Ассоциативный массив на упорядоченном списке пар ключ-значение.
     * Разработайте правила:
         * map_get(ListMap, Key, Value), проверяющее, что дерево содержит заданную пару ключ-значение.
         * map_put(ListMap, Key, Value, Result), добавляющее пару ключ-значение в дерево, или заменяющее текущее значение для ключа;
         * map_remove(ListMap, Key, Result), удаляющее отображение для ключа.
     * Правила не должны анализировать хвост списка, если в нем точно нет необходимого ключа.

  * **2. Сложный вариант.** Ассоциативный массив на двоичном дереве.
     * Разработайте правила:
         * tree_build(ListMap, TreeMap), строящее дерево из упорядоченного набора пар ключ-значение;
         * map_get(TreeMap, Key, Value).
     * Для решения можно реализовать любое дерево поиска логарифмической высоты.

  * **3. Бонусный вариант.** 
     * Дополнительно разработайте правила:
         *  map_put(TreeMap, Key, Value, Result);
         * map_remove(TreeMap, Key, Result).
 
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
