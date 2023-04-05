#pragma once

#include <iostream>

#include "Random.h"

class Player {
public:
    Player();

    std::vector<std::vector<char>> create();

    std::pair<int, int> shot(int result);

    int opponent_shot(const std::pair<int, int> &coords);
    
    void get_shot_res(int res);

    std::vector<std::vector<char>> field;

    enum Result {
        MISS = 0,
        SHOT = 1,
        KILL = 2
    };
    std::vector<std::vector<char>> _opponent_field;
private:
    enum Style {
        CENTER,
        BORDERS,
        RANDOM
    } _style;
    Random<unsigned> _random;
    unsigned _shotsCount;
    std::pair<int, int> _last_shot;

    bool check_cage(const std::pair<int, int> &coords);

    bool free_cage(const std::pair<int, int> &coords);

    void kill_ship(const std::pair<int, int> &startShip, const std::pair<int, int> &endShip);

    bool isMiss(const std::pair<int, int> &coords);

    std::pair<int, int> random_shot();
};