//
// Created by Roman Gostilo on 27.11.2021.
//

#include "Cell.h"

Cell::Cell()
{
    m_status = Wall;
    m_shape.setSize(sf::Vector2f(50, 50));
    m_shape.setFillColor(sf::Color::Black);
}

void Cell::setPos(int x, int y){
    m_shape.setPosition(x, y);
}

CELL Cell::GetStatus()
{
    return m_status;
}

void Cell::setAsPlayer(){
    m_status = Player;
    m_shape.setFillColor(sf::Color::Red);
}
void Cell::setAsWall(){
    m_status = Wall;
    m_shape.setFillColor(sf::Color::Black);
}
void Cell::setAsPass(){
    m_status = Pass;
    m_shape.setFillColor(sf::Color::White);
}

void Cell::setAsVisited()
{
    m_status = Visited;
    m_shape.setFillColor(sf::Color::Yellow);
}

void Cell::setAsExit()
{
    m_status = Exit;
    m_shape.setFillColor(sf::Color::Green);
}
