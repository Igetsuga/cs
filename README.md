# Практические работы по Обектно-ориентированному программированию

## ~~Практическая работа №1~~ 
- class: circle

## Практическая работа №2
- class: ArrayParent
- subclass: ArrayChild

Вопросы:
1. `quantity` и `capacity`, должны быть по разному устроены: `quantity`- количество элементов в массиве
   `capacity`- память для этих элементов в байтах, тогда `capacity = sizeof(type) * quantity` 
 
2. не понятно как работает `double* ptr;` 
 
3. не понятно как работает `ptr = new double[Dimension]`
 
4. строка 66- деконструктор, если бы мы не проверяли условие `(ptr != NULL)`, то что тогда удаляла бы функция `delete` ?

5. количество элементов в массиве `int arrSize = sizeof(arr)/sizeof(arr[0]);` или `std::array::size` 

6. сравнение double , (строка 221)
