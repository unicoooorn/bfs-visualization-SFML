//
// Created by Roman Gostilo on 27.11.2021.
//

#pragma once
#include <random>

inline double getTrueRandomNumber()
{
    static std::mt19937 rnd(std::random_device{}());
    static std::uniform_real_distribution<double> dist;
    return dist(rnd);
}

