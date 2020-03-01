## Технологии Программирования.
Чтобы запустить тесты, нужно:
* Download java_advanced
* Project Structure -> Project -> Project SDK
* Project Structure -> Project -> Project Compiler Output -> path\java_advanced\out
* Project Structure -> Modules -> Sources -> select src and Mark as Sources
* Build project (Ctrl + F9)
* Перенести .jar файлы из папок lib и artifacts в out/production/java_advanced (должно было сгенерироваться)
* Terminal -> Запускаемся из out/production/java_advanced

## [Домашнее задание 1. Обход файлов](https://github.com/nowiwr01/itmo/tree/master/java_advanced/src/ru/ifmo/rain/larionov/walk)
Разработайте класс `Walk`, осуществляющий подсчет хеш-сумм файлов
* Формат запуска: `java Walk <входной файл> <выходной файл>`
* Входной файл содержит список файлов, которые требуется обойти.
* Выходной файл должен содержать по одной строке для каждого файла. Формат строки: `<шестнадцатеричная хеш-сумма> <путь к файлу>`
* Для подсчета хеш-суммы используйте алгоритм [FNV](https://ru.wikipedia.org/wiki/FNV).
* Если при чтении файла возникают ошибки, укажите в качестве его хеш-суммы 00000000.
* Кодировка входного и выходного файлов — UTF-8.
* Если родительская директория выходного файла не существует, то соответствующий путь надо создать.
* Размеры файлов могут превышать размер оперативной памяти.

При выполнении задания следует обратить внимание на:
* Дизайн и обработку исключений, диагностику ошибок.
* Программа должна корректно завершаться даже в случае ошибки.
* Корректная работа с вводом-выводом.
* Отсутствие утечки ресурсов.

Input: 

```
java/info/kgeorgiy/java/advanced/walk/samples/1
java/info/kgeorgiy/java/advanced/walk/samples/12
java/info/kgeorgiy/java/advanced/walk/samples/123
java/info/kgeorgiy/java/advanced/walk/samples/1234
java/info/kgeorgiy/java/advanced/walk/samples/1
java/info/kgeorgiy/java/advanced/walk/samples/binary
java/info/kgeorgiy/java/advanced/walk/samples/no-such-file
```

Output:

```
050c5d2e java/info/kgeorgiy/java/advanced/walk/samples/1
2076af58 java/info/kgeorgiy/java/advanced/walk/samples/12
72d607bb java/info/kgeorgiy/java/advanced/walk/samples/123
81ee2b55 java/info/kgeorgiy/java/advanced/walk/samples/1234
050c5d2e java/info/kgeorgiy/java/advanced/walk/samples/1
8e8881c5 java/info/kgeorgiy/java/advanced/walk/samples/binary
00000000 java/info/kgeorgiy/java/advanced/walk/samples/no-such-file
```


Запуск:
* `java -cp . -p . -m info.kgeorgiy.java.advanced.walk Walk ru.ifmo.rain.larionov.walk.Walk`

## [Домашнее задание 2. Множество на массиве](https://github.com/nowiwr01/itmo/tree/master/java_advanced/src/ru/ifmo/rain/larionov/arrayset)
Разработайте класс `ArraySet`, реализующие неизменяемое упорядоченное множество.
* Класс `ArraySet` должен реализовывать интерфейс `SortedSet`.
* Все операции над множествами должны производиться с максимально возможной асимптотической эффективностью.

При выполнении задания следует обратить внимание на:
* Применение стандартных коллекций.
* Избавление от повторяющегося кода.

Запуск:
* `java -cp . -p . -m info.kgeorgiy.java.advanced.arrayset SortedSet ru.ifmo.rain.larionov.arrayset.ArraySet`

## [Домашнее задание 3. Студенты](https://github.com/nowiwr01/itmo/tree/master/java_advanced/src/ru/ifmo/rain/larionov/student)
Разработайте класс `StudentDB`, осуществляющий поиск по базе данных студентов.
* Класс `StudentDB` должен реализовывать интерфейс [StudentQuery](https://github.com/nowiwr01/itmo/blob/master/java_advanced/src/info/kgeorgiy/java/advanced/student/StudentQuery.java).
* Каждый метод должен состоять из ровно одного оператора. При этом длинные операторы надо разбивать на несколько строк.

При выполнении задания следует обратить внимание на:
* Применение лямбда-выражений и потоков.
* Избавление от повторяющегося кода.

Запуск:
* `java -cp . -p . -m info.kgeorgiy.java.advanced.student StudentQuery ru.ifmo.rain.larionov.student.StudentDB`
