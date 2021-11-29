//
// Created by Roman Gostilo on 27.11.2021.
//

#include "generator.h"


Generator::Generator(int size, Game* game)
        : field(size, game)
        , m_size(size)
{
    for (int y = 1; y < m_size; y += 2) {
        for (int x = 1; x < m_size; x += 2) {
            field.setCellStatus(position(x, y), CELL(Pass));
        }
    }
}

void Generator::buildMaze() {
    sf::Event event;
    while(field.m_board.window->pollEvent(event)){
        // закрытие на esc
        if (event.type == sf::Event::Closed ||
        (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            field.m_board.window->close();
    }

    position pos(1, 1);
    while (field.hasNotVisited()) {
        field.setCellStatus(pos, CELL::Visited);
        if (field.hasUnvisitedNeighbours(pos)) {
            usleep(10000);
            m_stack.push(pos);
            position newPos = field.pickRandNeighbour(pos);
            field.destroyWallBetween(pos, newPos);
            pos = newPos;
        } else if (!m_stack.empty()) {
            pos = m_stack.top();
            m_stack.pop();
        } else {
            pos = field.pickRandCell();
            field.setCellStatus(pos, CELL::Pass);
        }
        field.m_board.Refresh();
    }
    field.setCellStatus(pos, Exit);
    field.setCellAsExit(pos);

//    // делаем все visited клетки pass
//    for (int i = 0; i <= )
}
