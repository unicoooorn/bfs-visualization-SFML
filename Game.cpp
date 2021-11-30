//
// Created by Roman Gostilo on 27.11.2021.
//
#include "unistd.h"
#include "Game.h"
#include "generator.h"
#include <queue>

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
            temp[y_n]->setPos(x_n, y_n, cellLength);
            window->display();
        }
        m_cells.push_back(temp);
    }

    Generator my_gen(numOfCells, this);
    my_gen.buildMaze();
    setCellAsPlayer();

    for (int x_n = 0; x_n < numOfCells; x_n++){
        for (int y_n = 0; y_n < numOfCells; y_n++){
            if (m_cells[x_n][y_n]->GetStatus() == Visited){
                m_cells[x_n][y_n]->setAsPass();
            }
        }
    }
    Refresh();

    int m_size_clear = (m_size - 1) / 2;    // число вершин (в m_size учитываются боковые стенки и рёбра)
    int* distances = new int(m_size_clear * m_size_clear);
    int* prev = new int(m_size_clear * m_size_clear);
    printf("%d", m_player->getPos().x);
    distances[(m_player->getPos().y - 1) / 2 * m_size_clear + (m_player->getPos().x - 1) / 2] = 0;
    std::queue<Cell*> q;
    q.push(m_player);
    Refresh();
    bool toFound = true;
    while (toFound and q.empty() != true){
        Cell* u = q.front();
        q.pop();
        while (toFound and my_gen.field.hasPassToUnvisited(u->getPos())){
            sf::Event event;
            while(window->pollEvent(event)){
                // закрытие на esc
                if (event.type == sf::Event::Closed ||
                    (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                    window->close();
            }
            usleep(100000);
            position pos_tmp = my_gen.field.pickRandPass(u->getPos());
            if (m_cells[pos_tmp.x][pos_tmp.y]->GetStatus() == Exit){
                prev[(pos_tmp.y-1)/2*m_size_clear+(pos_tmp.x-1)/2] = (u->getPos().y-1)/2*m_size_clear+(u->getPos().x-1)/2;
                printf("в цикл зашкел!");
                my_gen.field.setCellAsPath(position( (pos_tmp.x + u->getPos().x) / 2, (pos_tmp.y + u->getPos().y) / 2) );
                while (true){
                    int tmp = prev[(pos_tmp.y-1)/2*m_size_clear+(pos_tmp.x-1)/2];

                    int y = tmp / m_size_clear;
                    int x = tmp -  y * m_size_clear;
                    my_gen.field.setCellAsPath(position( (pos_tmp.x + 2 * x + 1) / 2, (pos_tmp.y + 2 * y + 1) / 2) );
                    if (tmp == (m_player->getPos().y - 1) / 2 * m_size_clear + (m_player->getPos().x - 1) / 2){
                        toFound = false;
                        break;
                    }
                    pos_tmp = position(2 * x + 1, 2 * y + 1);
                    my_gen.field.setCellAsPath(pos_tmp);

                    Refresh();
                }
            }
            else{
                my_gen.field.setCellAsVisited(position( (pos_tmp.x + u->getPos().x) / 2, (pos_tmp.y + u->getPos().y) / 2) );
                my_gen.field.setCellAsVisited(pos_tmp);
                q.push(m_cells[pos_tmp.x][pos_tmp.y]);
                distances[(pos_tmp.y-1)/2*m_size_clear+(pos_tmp.x-1)/2]=distances[(u->getPos().y-1)/2*m_size_clear+(u->getPos().x-1)/2]+1;
                prev[(pos_tmp.y-1)/2*m_size_clear+(pos_tmp.x-1)/2] = (u->getPos().y-1)/2*m_size_clear+(u->getPos().x-1)/2;
                Refresh();
            }
        }
    }
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
    else if (status == Path){
        m_cells[pos.x][pos.y]->setAsPath();
    }
}

void Game::setCellAsExit(position pos)
{
    m_cells[pos.x][pos.y]->setAsExit();
}

void Game::setCellAsPlayer(){
    m_player_x = m_size - 2;
    m_player_y = m_size - 2;
    m_player = m_cells[m_player_x][m_player_y];
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