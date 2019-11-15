## [Домашнее задание 1. Сумма чисел](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW1)
Раззработайте класс Sum, который при запуске из командной строки будет складывать переданные в качестве аргументов целые числа и выводить их сумму на консоль.
 
Модификации
 * *DoubleSpace*
    * Входные данные являются числами с формате с плавающей точкой
    * Класс должен иметь имя `SumDoubleSpace`
    * Числа разделяются [пробелами-разделителями](https://docs.oracle.com/javase/8/docs/api/java/lang/Character.html#SPACE_SEPARATOR)
    * [Откомпилированные тесты](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW1/SumDoubleSpace/SumDoubleSpaceTest.jar)
 * *BigIntegerDigit*
    * Входные данные помещаются в тип [BigInteger](https://docs.oracle.com/javase/8/docs/api/java/math/BigInteger.html)
    * Класс должен иметь имя `SumBigInteger`
    * Числа имеют вид `[знак]цифры`
    * [Откомпилированные тесты](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW1/SumBigInteger/SumBigIntegerDigitTest.jar)
   
## [Домашнее задание 2. Реверс](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW2/)
Разработайте класс Reverse, читающий числа из стандартного входа, и выводящий их на стандартный вывод в обратном порядке.
 
В каждой строке входа содержится некоторое количество целых чисел (может быть 0). Числа разделены пробелами. Каждое число помещается в тип int.
 
Порядок строк в выходе должен быть обратным по сравнению с порядком строк во входе. Порядок чисел в каждой строке так же должен быть обратным к порядку чисел во входе.
 
Input:
 
```
1
 
2 -3
```
 
Output:
 
```
-3 2
 
1
```
 
Модификации
 * *Транспозиция*
    * Рассмотрим входные данные как (не полностью определенную) матрицу,
      выведите ее в транспонированном виде
    * Класс должен иметь имя `ReverseTranspose`
    * [Откомпилированные тесты](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW2/ReverseTranspose/ReverseTransposeTest.jar)
 * *Максимум*
    * Рассмотрим входные данные как (не полностью определенную) матрицу,
      вместо каждого числа выведите максимум из чисел в его столбце и строке.
    * Класс должен иметь имя `ReverseMax`
    * [Откомпилированные тесты](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW2/ReverseMax/ReverseMaxTest.jar)    
   
## [Домашнее задание 3. Сумма чисел в файле](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW3/)
Описание совпадает с HW1. Добавляем к этому всему файлы и обработку ошибок.
 
Модификации
 * *Hex*
    * На вход подаются десятичные и шестнадцатеричные числа
    * Шестнадцатеричные числа имеют префикс `0x`
    * Ввод регистронезависим
    * Класс должен иметь имя `SumHexFile`
    * [Откомпилированные тесты](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW3/SumHexFile/SumHexFileTest.jar)
 * *Abc*
    * На вход подаются числа, представленные буквами.
      Нулю соответствует буква `a`, единице – `b` и так далее
    * Ввод регистронезависим
    * Класс должен иметь имя `SumAbcFile`
    * [Откомпилированные тесты](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW3/SumAbcFile/SumAbcFileTest.jar)
 
## [Домашнее задание 4. Статистика слов](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW4/)
Разработайте класс WordStat, который будет подсчитывать статистику встречаемости слов во входном файле.
 
Словом называется непрерывная последовательность букв, апострофов и тире (Unicode category Punctuation, Dash). Для подсчета статистики, слова приводятся к нижнему регистру.
 
Выходной файл должен содержать все различные слова, встречающиеся во входном файле, в порядке их появления. Для каждого слова должна быть выведена одна строка, содержащая слово и число его вхождений во входной файл.
 
Input:
```
Monday's child is fair of face.
Tuesday's child is full of grace.
```
 
Output:
```
monday's 1
child 2
is 2
fair 1
of 2
face 1
tuesday's 1
full 1
grace 1
 ```
 
Модификации
 * *Words*
    * В выходном файле слова должны быть упорядочены в лексикографическом порядке
    * Класс должен иметь имя `WordStatWords`
    * [Откомпилированные тесты](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW4/WordStatWords/WordStatWordsTest.jar)
 * *Count*
    * В выходном файле слова должны быть упорядочены по возрастанию числа
      вхождений, а при равном числе вхождений – по порядку первого вхождения
      во входном файле
    * Класс должен иметь имя `WordStatCount`
    * [Откомпилированные тесты](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW4/WordStatCount/WordStatCountTest.jar)
   
## [Домашнее задание 5. Быстрый реверс](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW5/)
Реализуйте свой аналог класса Scanner на основе Reader.
 
Примените разработанный Scanner для решения задания «Реверс».
 
Модификации
 * *ReverseSum*
    * Рассмотрим входные данные как (не полностью определенную) матрицу,
      вместо каждого числа выведите сумму чисел в его столбце и строке.
    * Класс должен иметь имя `ReverseSum`
    * [Откомпилированные тесты](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW5/ReverseSumFastTest.jar)
   
## [Домашнее задание 6. Статистика слов++](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW6/)
Разработайте класс WordStatIndex, который будет подсчитывать статистику встречаемости слов во входном файле.
 
Словом называется непрерывная последовательность букв, апострофов и тире (Unicode category Punctuation, Dash). Для подсчета статистики, слова приводятся к нижнему регистру.
 
Выходной файл должен содержать все различные слова, встречающиеся во входном файле, в порядке их появления. Для каждого слова должна быть выведена одна строка, содержащая слово, число его вхождений во входной файл и номера вхождений этого слова среди всех слов во входном файле.
 
Имена входного и выходного файла задаются в качестве аргументов командной строки. Кодировка файлов: UTF-8.
 
Программа должна работать за линейное от размера входного файла время.
 
Для реализации программы используйте Collections Framework.
 
Модификации
 * *LineIndex*
    * В выходном файле слова должны быть упорядочены в лексикографическом порядке
    * Вместо номеров вхождений во всем файле надо указывать
      `<номер строки>:<номер в строке>`
    * Класс должен иметь имя `WordStatLineIndex`
    * [Откомпилированные тесты](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW6/WordStatLineIndexTest.jar)
   
 
## [Домашнее задание 7. Бинарный поиск с контрактами](https://github.com/nowiwr01/itmo/blob/master/prog_intro/HW7/search/BinarySearchMissing.java)
Модификации
* *MissingTest*
    * Если в массиве `a` отсутствует элемент, равный `x`, то требуется
      вывести индекс вставки в формате, определенном в
      [`Arrays.binarySearch`](http://docs.oracle.com/javase/8/docs/api/java/util/Arrays.html#binarySearch-int:A-int-).
    * Класс должен иметь имя `BinarySearchMissing`
    * [Откомпилированные тесты](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW7//BinarySearchMissingTest.jar)
    
## [Домашнее задание 8. Очередь на массиве с контрактами](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW8/queue)
Модификации
 * *toArray*
    * Реализовать метод `toArray`, возвращающий массив,
      содержащий элементы, лежащие в очереди в порядке
      от головы к хвосту.
    * Исходная очередь должна остаться неизменной
    * Дублирования кода быть не должно
    * [Откомпилированные тесты](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW8/ArrayQueueToArrayTest.jar)
    
## [Домашнее задание 9. Очередь на связном списке](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW9/queue)
Модификации
 * *QueueToArray*
    * Добавить в интерфейс очереди и реализовать метод
      `toArray`, возвращающий массив,
      содержащий элементы, лежащие в очереди в порядке
      от головы к хвосту
    * Исходная очередь должна оставаться неизменной
    * Дублирования кода быть не должно
    * [Откомпилированные тесты](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW9/QueueToArrayTest.jar)
    
## [Домашнее задание 10. Вычисление выражений](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW10/src/expression)
Парсер арифметических выражений
 
Модификации
 * *Базовая*
    * Реализовать интерфейс [Expression](https://github.com/nowiwr01/itmo/blob/master/prog_intro/HW10/src/expression/Expression.java)
    * [Исходный код тестов](https://github.com/nowiwr01/itmo/blob/master/prog_intro/HW10/src/expression/ExpressionTest.java)
 * *DoubleExpression*
    * Реализовать интерфейс [DoubleExpression](https://github.com/nowiwr01/itmo/blob/master/prog_intro/HW10/src/expression/DoubleExpression.java)
    * [Исходный код тестов](https://github.com/nowiwr01/itmo/blob/master/prog_intro/HW10/src/expression/DoubleExpressionTest.java)

## [Домашнее задание 11. Разбор выражений](https://github.com/nowiwr01/itmo/tree/master/prog_intro/HW10/src/expression)
Прокаченный парсер арифметических выражений
  
Модификации
 * *Базовая*
    * Класс `ExpressionParser` должен реализовывать интерфейс
        [Parser](https://github.com/nowiwr01/itmo/blob/master/prog_intro/HW11/src/expression/parser/Parser.java)
    * Результат разбора должен реализовывать интерфейс
        [TripleExpression](https://github.com/nowiwr01/itmo/blob/master/prog_intro/HW11/src/expression/TripleExpression.java)
    * [Исходный код тестов](https://github.com/nowiwr01/itmo/blob/master/prog_intro/HW11/src/expression/parser/ParserTest.java)
 * *ParserBitwise*
    * Дополнительно реализовать бинарные операции:
        * `&` — побитное И, приоритет меньше чем у `+` (`6 & 1 + 2` равно `6 & (1 + 2)` равно 2);
        * `^` — побитный XOR, приоритет меньше чем у `&` (`6 ^ 1 + 2` равно `6 ^ (1 + 2)` равно 5);
        * `|` — побитное ИЛИ, приоритет меньше чем у `^` (`6 | 1 + 2` равно `6 | (1 + 2)` равно 7);
    * [Исходный код тестов](https://github.com/nowiwr01/itmo/blob/master/prog_intro/HW11/src/expression/parser/ParserBitwiseTest.java)
  

