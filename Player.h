#pragma once

#include <iostream>

#define NOTHING_CHAR '.'
#define MISS_CHAR 'M'
#define SHIP_CHAR 'X'
#define SHOT_CHAR 'S'

#define MAX_INDEX 9

#define CENTER_SHOTS_COUNT 2
#define BORDER_SHOTS_COUNT 6

#define DIRS_NUM 3

#include "Random.h"
#include "IPlayer.hpp"

class Player : public IPlayer {
public:
    typedef std::pair<int, int> CoordsT;

    Player();

    std::vector<std::vector<char>> create() override;
    std::unordered_set<CoordsT, hash<pair<int, int>>> unchecked_cages;

    CoordsT shot() override;

    int opponent_shot(CoordsT coords) override;

    void get_shot_res(int res);

    std::vector<std::vector<char>> field;

    enum Result {
        UNDEFINED = -1,
        MISS = 0,
        SHOT = 1,
        KILL = 2
    };


    std::vector<std::vector<char>> _opponentField;

    string team_name() override;

private:
    enum Style {
        CENTER,
        BORDERS,
        RANDOM
    } _style;
    Random<unsigned> _random;
    unsigned _shotsCount;
    CoordsT _lastShot;
    CoordsT _prevLastShot;
    Result _lastResult;
    CoordsT _lastDirection;
    bool _firstShot;
    bool _isLastHit;
    int _directionsX[DIRS_NUM], _directionsY[DIRS_NUM];

    std::pair<CoordsT, CoordsT> getOpponentShip(const CoordsT &coords);

    bool checkCage(const CoordsT &coords);

    void killShip(const CoordsT &startShip, const CoordsT &endShip);

    bool isMiss(const CoordsT &coords);
    bool isInRange(const CoordsT &coords);

    CoordsT random_shot();
};