//
// Created by Roman Gostilo on 27.11.2021.
//

#include <SFML/Graphics.hpp>
#pragma once

enum CELL {
    Visited, Pass, Wall, Player, Exit
};

struct position {
    int x, y;
    position(int x, int y) : x(x), y(y){}
};

class Cell
{
    CELL m_status;

public:
    void setPos(int x, int y);
    sf::RectangleShape m_shape;
    Cell();
    CELL GetStatus();   // возвращает статус клетки
    void setAsPlayer(); // делает клетку игроком
    void setAsWall();   // делает клетку стеной
    void setAsPass();   // делает клетку проходом
    void setAsVisited();    // делает клетку посещенным проходом
    void setAsExit();
};
