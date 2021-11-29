//
// Created by Roman Gostilo on 27.11.2021.
//

#pragma once
#include <stack>
#include "generatorhelper.h"
#include "Game.h"
#include <unistd.h>

class Generator{
    int m_size;
public:
    std::stack<position> m_stack;
    GeneratorHelper field;
    Generator(int size, Game* game);
    void buildMaze();
};
