# Лабораторная работа: Крестики-нолики 10x10

Консольная реализация игры крестики-нолики 10x10 (5 в ряд) с поддержкой динамической загрузки режимов отображения.

## Основные особенности
- Поддержка двух режимов отображения:
    - **Компактный** (символьное представление)
    - **Графический** (ASCII-арт с псевдографикой)
- Архитектура Model-View:
    - Модель игры (`tictactoe::Game`) содержит всю игровую логику
    - Режимы отображения реализованы как разделяемые библиотеки
- Динамическое переключение режимов во время игры
- Корректная обработка ввода и проверка ходов
- Определение победителя и ничьей


## Сборка и запуск
```bash
mkdir build && cd build
cmake ..
make

# Запуск с компактным отображением
./tic-tac-toe compact-view

# Запуск с графическим отображением
./tic-tac-toe view-pretty

# Во время игры можно переключать режимы командой вида "view-название_режима"