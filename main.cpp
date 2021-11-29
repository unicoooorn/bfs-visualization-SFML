#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "unistd.h"
#include "Cell.h"
#include "Game.h"

int main()
{
    Game* myGame = new Game();

    while(myGame->window.isOpen())
    {
        // Обрабатываем события в цикле
        sf::Event event;
        while(myGame->window.pollEvent(event))
        {
            // Кроме обычного способа наше окно будет закрываться по нажатию на Escape
            if(event.type == sf::Event::Closed ||
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                myGame->window.close();
        }



        // Очистка
        myGame->window.clear();
        // Тут будут вызываться функции обновления и отрисовки объектов
        // Отрисовка
        for (int i = 0; i < myGame->numOfCells; i++){
            for (int k = 0; k < myGame->numOfCells; k++){
                myGame->window.draw(myGame->m_cells[k][i]->m_shape);
            }
        }
        myGame->window.display();
    }

    return 0;
}