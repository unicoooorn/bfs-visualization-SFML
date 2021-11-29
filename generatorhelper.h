//
// Created by Roman Gostilo on 27.11.2021.
//

#pragma once
#include "Game.h"
#include "true_random.h"

class GeneratorHelper {   // вспомогательный класс для генератора лабиринта
    int m_size = 0;
    bool m_isPass(position);
public:
    Game& m_board;
    GeneratorHelper(int size, Game* game);
    int getMazeSize();
    bool hasNotVisited();
    bool hasUnvisitedNeighbours(position);
    void destroyWallBetween(position, position);
    // выбор клетки
    position pickRandCell();    // взять рандомную клетку
    position pickRandNeighbour(position);   // взять рандомного соседа к данной клетке
    CELL getCellStatus(position);
    void setCellStatus(position, CELL);
    void setCellAsVisited(position);
    void setCellAsExit(position);
};
