//
// Created by Roman Gostilo on 27.11.2021.
//

#include "generatorhelper.h"

bool GeneratorHelper::m_isPass(position pos){
    return m_board.getCellStatus(pos) == CELL::Pass;
}

void GeneratorHelper::setCellAsExit(position pos)
{
    m_board.setCellAsExit(pos);
}

GeneratorHelper::GeneratorHelper(int size, Game* game)
        : m_size(size)
        , m_board(*game)
{
}

int GeneratorHelper::getMazeSize() {
    return m_size;
}

void GeneratorHelper::setCellAsVisited(position pos) {
    m_board.setCellStatus(pos, CELL::Visited);
}

bool GeneratorHelper::hasNotVisited() {
    for (int y = 1; y < m_size; y++) {
        for (int x = 1; x < m_size; x++) {
            position p = position(x, y);
            if (m_board.getCellStatus(p) == CELL::Pass) {
                return true;
            }
        }
    }
    return false;
}

bool GeneratorHelper::hasUnvisitedNeighbours(position pos) {
    int x = pos.x;
    int y = pos.y;
    if (m_isPass(position(x, y - 2))) return true;
    if (m_isPass(position(x + 2, y))) return true;
    if (m_isPass(position(x, y + 2))) return true;
    if (m_isPass(position(x - 2, y))) return true;
    return false;
}

void GeneratorHelper::destroyWallBetween(position left, position right) {
    int lx = left.x;
    int ly = left.y;
    int rx = right.x;
    int ry = right.y;
    position wall_position = position((lx + rx) / 2, (ly + ry) / 2);
    m_board.setCellStatus(wall_position, CELL::Visited);
}

position GeneratorHelper::pickRandCell() {
    while (true) {
        int x = static_cast<int>(getTrueRandomNumber() * m_size);
        int y = static_cast<int>(getTrueRandomNumber() * m_size);
        position pos(x, y);
        if (m_board.getCellStatus(pos) == CELL::Pass) {
            return pos;
        }
    }
}

position GeneratorHelper::pickRandNeighbour(position pos)
// предусловие: свободные соседи есть
{
    int x = pos.x;
    int y = pos.y;
    while (true) {
        int rand_int = static_cast<int>(getTrueRandomNumber() * 4);
        int dx = 0, dy = 0;
        switch (rand_int) {
            case 0:
                dy = -2;
                break;
            case 1:
                dx = 2;
                break;
            case 2:
                dy = 2;
                break;
            case 3:
                dx = -2;
                break;
        }
        position new_position(x + dx, y + dy);
        if (m_isPass(new_position)) {

            return new_position;
        }
    }
}

void GeneratorHelper::setCellStatus(position pos, CELL value) {
    m_board.setCellStatus(pos, value);
}

CELL GeneratorHelper::getCellStatus(position pos) {
    return m_board.getCellStatus(pos);
}
