FVM
===

Программное обеспечение для поддержки функционально-воксельных методов компьютерного моделирования. Основные вычислительные конструкции основаны на локальных геометрических характеристиках, представленных воксельным скалярным полем.

![FVM](https://i.imgur.com/wfeB2ER.jpg)

Features
------
- Формирование функционально-воксельной модели функции
- Отображение графического представления функции на заданном диапазоне
- Отображение графического представления функционально-воксельной модели на заданном дипазоне

Installation
------
    gitclone https://github.com/leeroyka/FVM.git
    cd FVM
    mkdir build && cd build
    cmake .. && cmake --build .
    make install
Dependencies
------
- [MathEvaluator]((https://github.com/KJ002/MathEvaluator)
- [simple-matrix](https://github.com/torin-carey/simple-matrix)

TODO
------
- [ ] Добавить обработку ошибок
- [ ] Распаралелить алгоритм построения воксельной модели
- [ ] Проверка валидности строки