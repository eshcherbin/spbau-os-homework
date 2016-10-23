# Домашние задания по ОС

## Задание №1
#### Основные пункты
* В `serial.c` реализованы базовые действия с последовательным портом

* В `interrupt.c` реализована инициализация IDT и контроллера прерываний, а также общая часть обработчика прерываний
  В `int_wrappers.S` находятся все 256 обработчиков, которые устроены практически одинаково

* В `timer.c` реализована инициализация PIT

#### Дополнительные пункты
* В `io.c` реализованы функции семейства `printf`

* В `backtrace.c` реализован вывод стек вызовов

## Задание №2
#### Основные пункты
* В `memmap.c` находится получение карты памяти.
  В `paging.c` реализован базовый функционал настройки отображения виртуальных адресов на физические

* В `buddy_alloc.c` реализован Buddy Allocator

* В `block_alloc.c` реализован аллокатор блоков одинакового размера

#### Дополнительные пункты
* В `mem_alloc.c` находится аллокатор общего назначения
