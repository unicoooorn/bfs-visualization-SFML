//
// Created by Roman Gostilo on 27.11.2021.
//
#include "unistd.h"
#include "Game.h"
#include "generator.h"

// обновление экрана
void Game::Refresh(){
    window->clear();
    for (int i = 0; i < numOfCells; i++){
        for (int k = 0; k < numOfCells; k++){
            window->draw(m_cells[k][i]->m_shape);
        }
    }
    window->display();
}

Game::Game(){
    cellLength = 35;
    mazeLength = 1435; // mazeLength % cellLength = 0
    numOfCells = mazeLength / cellLength;
    m_size = mazeLength / cellLength;

    window = new sf::RenderWindow(sf::VideoMode(mazeLength, mazeLength), "Maze");
    // заполнение массива
    for (int x_n = 0; x_n < numOfCells; x_n++){
        std::vector<Cell*> temp;
        for (int y_n = 0; y_n < numOfCells; y_n++){
            Cell * tmp = new Cell;
            temp.push_back(tmp);
            temp[y_n]->setPos(x_n * cellLength, y_n * cellLength);
            window->display();
        }
        m_cells.push_back(temp);
    }

    Generator my_gen(numOfCells, this);
    my_gen.buildMaze();
}

// интерфейс для изменения статуса клетки
void Game::setCellStatus(position pos, CELL status)
{
    if (status == Visited){
        m_cells[pos.x][pos.y]->setAsVisited();
    }
    else if (status == Pass){
        m_cells[pos.x][pos.y]->setAsPass();
    }
    else if (status == Wall){
        m_cells[pos.x][pos.y]->setAsWall();
    }
}

void Game::setCellAsExit(position pos)
{
    m_cells[pos.x][pos.y]->setAsExit();
}

void Game::setCellAsPlayer(){
    m_player_x = m_size - 2;
    m_player_y = m_size - 2;
    m_cells[m_player_x][m_player_y]->setAsPlayer();
}

// интерфейс для получения статуса клетки - Wall, Pass, Visited, Player
CELL Game::getCellStatus(position pos)
{
    if (pos.x < 0 || pos.x >= m_size || pos.y < 0 || pos.y >= m_size){
        return Wall;
    }
    return m_cells[pos.x][pos.y]->GetStatus();
}


Game::~Game()
{
    delete window;
}