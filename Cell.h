//
// Created by Roman Gostilo on 27.11.2021.
//

#include <SFML/Graphics.hpp>
#pragma once

enum CELL {
    Visited, Pass, Wall, Player, Exit, Path
};

struct position {
    int x, y;
    position(int x, int y) : x(x), y(y){}
    position() : x(0), y(0){}
};

class Cell
{
    CELL m_status;
    position m_pos;
public:
    void setPos(int x, int y, int cellLength);
    position getPos();

    sf::RectangleShape m_shape;
    Cell();
    CELL GetStatus(); // возвращает статус клетки
    void setAsPlayer(); // делает клетку игроком
    void setAsWall();   // делает клетку стеной
    void setAsPass();   // делает клетку проходом
    void setAsPath();   // делает клетку частью кратчайшего пути
    void setAsVisited();    // делает клетку посещенным проходом
    void setAsExit();
};
