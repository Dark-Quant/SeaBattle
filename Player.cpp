#include "Player.h"

Player::Player()
        : _random{}, _style{Style::CENTER}, _shotsCount{}, _lastResult{Result::MISS}, _lastShot{},
          _lastDirection{}, _firstShot{true}, _isLastHit{false}, _directionsX{-1, 0, 1}, _directionsY{-1, 0, 1},
          _prevLastShot{} {}

std::vector<std::vector<char>> Player::create() {
    field.resize(10, std::vector<char>(10, NOTHING_CHAR));
    _opponentField.resize(10, std::vector<char>(10, NOTHING_CHAR));
    unsigned startY, endY, startX, endX, direction;
    int dy, dx;
    std::pair coords{0, 0};

    for (uint8_t length = 4; length != 0; --length) {
        for (uint8_t count = 0; count < 5 - length; ++count) {
            endY = endX = 9;
            startY = startX = dy = dx = 0;
            direction = _random(0, 3);
            switch (direction) {
                case 0: // ->
                    endX = 10 - length;
                    dx = 1;
                    break;
                case 1: // v
                    endY = 10 - length;
                    dy = 1;
                    break;
                case 2: // <-
                    startX = length - 1;
                    dx = -1;
                    break;
                case 3: // ^
                    startY = length - 1;
                    dy = -1;
                    break;
            }
            std::pair last_coords{0, 9};
            do {
                coords = {_random(startX, endX), _random(startY, endY)};
                last_coords = {coords.first + dx * (length - 1), coords.second + dy * (length - 1)};
            } while (!check_cage(coords) ||
                     !check_cage(last_coords));
            auto [x, y] = coords;
            for (int i = 0; i < length; ++i) {
                field[y][x] = SHIP_CHAR;
                y += dy;
                x += dx;
            }
        }
    }
    // X - корабль
    // .....XXXX..
    //1 - 4палубный
    //2 - 3палубных
    //3 - 2палубных
    //4 - 1палубных
    //M - shot void
    //S - shot on shi[
    return field;
}

Player::CoordsT Player::shot() {
//    ++_shotsCount;
//    _prevLastShot = _lastShot;
//    auto &[x, y] = _lastShot;
//    switch (_lastResult) {
//        case Result::KILL: {
//            auto [start, end] = get_opponent_ship(_lastShot);
//            kill_ship(start, end);
//            _lastShot = random_shot();
//            _isLastHit = false;
//        }
//            break;
//        case Result::MISS:
//            _opponentField[_lastShot.second][_lastShot.first] = MISS_CHAR;
//            if (!_isLastHit) {
//                _lastShot = random_shot();
//                break;
//            }
//        case Result::SHOT: {
//            auto &[dirX, dirY] = _lastDirection;
//            if (_firstShot && _opponentField[_lastShot.second][_lastShot.first] == 'S') {
//                _firstShot = false;
//            } else if (_firstShot) {
//                do {
//                    x = _lastShot.first;
//                    y = _lastShot.second;
//                    switch (_random(0, 3)) {
//                        case 0:
//                            x += 1;
//                            break;
//                        case 1:
//                            x -= 1;
//                            break;
//                        case 2:
//                            y += 1;
//                            break;
//                        case 3:
//                            y -= 1;
//                            break;
//                    }
//                } while (_opponentField[y][x] == 'M');
//            }
//            if (dirX == 0 && dirY == 0 && !_firstShot) {
//                dirX = _lastShot.first - _prevLastShot.first;
//                dirY = _lastShot.second - _prevLastShot.second;
//            }
//
//            if (_opponentField[y][x] == MISS_CHAR) {
//                dirX *= -1;
//                dirY *= -1;
//            }
//
//            while (_opponentField[y][x] == SHOT_CHAR) {
//                x += dirX;
//                y += dirY;
//            }
//
//            _isLastHit = true;
//        }
//            break;
//    }
//    return _lastShot;
    return {_random(0, 9), _random(0, 9)};
}

int Player::opponent_shot(Player::CoordsT coords) {
    auto [y, x] = coords;

    if (field[y][x] == NOTHING_CHAR)
        return Result::MISS;

    field[y][x] = SHOT_CHAR;
    int nextX, nextY;
    for (int dirY: _directionsY) {
        for (int dirX: _directionsX) {
            nextX = x + dirX;
            nextY = y + dirY;
            if (nextX < 0 || nextX > MAX_INDEX || nextY < 0 || nextY > MAX_INDEX) continue;
            if (field[nextY][nextX] == NOTHING_CHAR) continue;
            if (field[nextY][nextX] == SHIP_CHAR) return Result::SHOT;
            while (field[nextY][nextX] != NOTHING_CHAR) {
                if (nextX < 0 || nextX > MAX_INDEX || nextY < 0 || nextY > MAX_INDEX) {
                    break;
                }
                if (field[nextY][nextX] == SHIP_CHAR) {
                    return Result::SHOT;
                }
                nextX += dirX;
                nextY += dirY;
            }
        }
    }
    return Result::KILL;
}

bool Player::check_cage(const Player::CoordsT &coords) {
    auto [x, y] = coords;
    for (int i = std::max(y - 1, 0); i <= std::min(y + 1, 9); i++) {
        for (int j = std::max(x - 1, 0); j <= std::min(x + 1, 9); j++) {
            if (i == x && j == y) continue;
            if (field[i][j] == SHIP_CHAR || field[i][j] == SHOT_CHAR) {
                return false;
            }
        }
    }
    return true;
}

void Player::kill_ship(const Player::CoordsT &startShip, const Player::CoordsT &endShip) {
    auto [startX, startY] = startShip;
    auto [endX, endY] = endShip;
    for (int i = std::max(startY - 1, 0); i <= std::min(endY + 1, 9); ++i) {
        for (int j = std::max(startX - 1, 0); j <= std::min(endX + 1, 9); ++j) {
            if ((i >= startY && i <= endY) && (j >= startX && j <= endX)) continue;
            _opponentField[i][j] = MISS_CHAR;
        }
    }
}

bool Player::isMiss(const Player::CoordsT &coords) {
    const auto &[x, y] = coords;
    return _opponentField[y][x] == MISS_CHAR;
}

Player::CoordsT Player::random_shot() {
    unsigned x{}, y{};
    switch (_style) {
        case Style::CENTER:
            do {
                x = _random(4, 5);
                y = _random(4, 5);
            } while (isMiss({x, y}));
            if (_shotsCount == CENTER_SHOTS_COUNT) {
                _style = Style::BORDERS;
            }
            break;

        case Style::BORDERS:
            if (_random(0, 1)) {
                do {
                    x = _random(0, 1) * MAX_INDEX;
                    y = _random(0, MAX_INDEX);
                } while (isMiss({x, y}));
            } else {
                do {
                    y = _random(0, 1) * MAX_INDEX;
                    x = _random(0, MAX_INDEX);
                } while (isMiss({x, y}));
            }
            if (_shotsCount == BORDER_SHOTS_COUNT) {
                _style = Style::RANDOM;
            }
            break;

        case Style::RANDOM:
            do {
                x = _random(0, 9);
                y = _random(0, 9);
            } while (isMiss({x, y}));
            break;
    }
    return {x, y};
}

void Player::get_shot_res(int res) {
    _lastResult = static_cast<Result>(res);
}

std::pair<Player::CoordsT, Player::CoordsT> Player::get_opponent_ship(const Player::CoordsT &coords) {
    auto [x, y] = coords;
    int directionsX[] = {-1, 0, 1}, directionsY[] = {-1, 0, 1};
    int nextX, nextY;
    CoordsT startShip, endShip;

    for (int dirY: directionsY) {
        for (int dirX: directionsX) {
            nextX = x + dirX;
            nextY = y + dirY;
            if (nextX < 0 || nextX > MAX_INDEX || nextY < 0 || nextY > MAX_INDEX) continue;
            if (field[nextY][nextX] == NOTHING_CHAR) continue;
            startShip = {x, y};
            endShip = {x, y};
            while (field[nextY][nextX] != NOTHING_CHAR) {
                if (nextX < 0 || nextX > MAX_INDEX || nextY < 0 || nextY > MAX_INDEX) {
                    break;
                }
                startShip = std::min(startShip, {nextX, nextY});
                endShip = std::max(endShip, {nextX, nextY});
                nextX += dirX;
                nextY += dirY;
            }
        }
    }
    return {startShip, endShip};
}

string Player::team_name() {
    return "Lopushok";
}