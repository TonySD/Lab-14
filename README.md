# Лабораторная работа №14
Дата выдачи: 2023-01-01.
Срок выполнения: 2023-05-13.

## Си++11/14/17 - параллелизация вычислений и работа с файловой системой

### Ответвление
Необходимо создать ответвление (fork) моего репозитория Lab-14 (название
оставить без изменения, а видимость поставить приватной). Назничить меня в
новом репозитории соавтором с правами администратора. Вики, Задачи а также
Проекты отключить.

В локальной копии создавать ветки (branch) по необходимости.

### Этап разработки
Разработать консольную утилиту позволяющую выполнять проверку целостности 
файлов на основе механизма контрольных сумм. При запуске программа проверяет 
наличие файла `Checksum.ini`. При его наличия выполняется проверка 
контрольных сумм для файлов указанных в нем, иначе если поток ввода не пуст, 
то из него считывается имя файла(ов) и, отделенные символом табуляции, 
их контрольные суммы (см. ключ `-a`). Если поток ввода пуст, проводится разбор 
параметров командной строки и, в зависимости от входных данных, выполняется 
действие либо выводится `usage`.

Режимы запуска программы:
  * без параметров - использование файла `Checksum.ini`;
  * `-a algorithm`, где `algorithm` одно из `crc32`, `md5`, `sha256` - задаёт 
    алгоритм для рассчёта контрольной суммы;
  * `файл...` - имена файлов для вычисления контрольных сумм (см. ключ `-a`).

Пример содержимого файла `Checksum.ini`:
```
; This is comment
[CRC32]
README.md=0x720C65BA
```

#### Асинхронное программирование на основе задач
При разработке программы реализовать асинхронный алгоритм обработки данных 
с использованием возможностей `std::async`.

#### Взаимодействие с файловой системой
Для взаимодействия с файловой системой использовать возможности 
`std::filesystem`.

По выполненной работе составить отчет по ГОСТ 7.32 включающий описание 
разработанных классов. Отчет в обязательном порядке должен содержать UML 2.0 
диаграмму классов. Отчет включить в состав исходных кодов программы в виде 
файла формата PDF.

Дополнительная информация:
  * Мейерс С. Эффективный и современный С++ (глава 7)
  * Галовиц Я. С++17 STL. Стандартная библиотека шаблонов (глава 10)
  * Уильямс Э. C++. Практика многопоточного программирования (глава 4)
  * Гримм Р. Параллельное программирование на современном языке C++ (глава 3)
  * https://en.cppreference.com/w/cpp/thread/async
  * https://en.cppreference.com/w/cpp/filesystem
  * [certutil](https://learn.microsoft.com/en-us/windows-server/administration/windows-commands/certutil#-hashfile)
  * [cksum](https://www.opennet.ru/man.shtml?topic=cksum&category=1&russian=1)
  * [md5sum](https://www.opennet.ru/man.shtml?topic=md5sum&category=1&russian=2)
  * [sha256sum](https://www.opennet.ru/man.shtml?topic=sha256sum&russian=2)

### Запрос слияния
По итогу выполнения работы создать запрос на слияние (pull request) 
и назначить меня рецензентом.

