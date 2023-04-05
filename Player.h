#pragma once

#include <iostream>

#include "Random.h"

class Player {
public:
    Player();

    std::vector<std::vector<char>> create();

    std::pair<int, int> shot();

    int opponent_shot(std::pair<int, int> p);

    std::vector<std::vector<char>> field;
private:
    Random _random;
};