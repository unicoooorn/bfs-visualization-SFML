//
// Created by Roman Gostilo on 27.11.2021.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"


class Game{
public:
    Game();
    Game(int cellLength, int mazeLength);   // создание поля
    sf::RenderWindow* window;
    int cellLength;
    int mazeLength; // mazeLength % cellLength = 0
    int numOfCells;
    std::vector<std::vector<Cell*>> m_cells;
    void Refresh();
    Cell* m_player;
    int m_size;
    int m_player_x, m_player_y; // координаты игрока
    void setCellStatus(position, CELL);  // устанавливает статус клетки (Visited, Pass, Wall, Player, Exit)
    void setCellAsPlayer(); // ставим игрока
    void setCellAsExit(position);   // ставим выход
    ~Game();
    CELL getCellStatus(position);    // возвращает статус клетки (Visited, Pass, Wall, Player, Exit)
    int getMazeSize(); // возвращает размер лабиринта в клетках
};