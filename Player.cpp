#include "Player.h"

#define NOTHING_CHAR '.'
#define MISS_CHAR 'M'
#define SHIP_CHAR 'X'
#define SHOT_CHAR 'S'

#define MAX_INDEX 9

#define CENTER_SHOTS_COUNT 2
#define BORDER_SHOTS_COUNT 6

Player::Player() : _random{}, _style{Style::CENTER}, _shotsCount{} {}

std::vector<std::vector<char>> Player::create() {
    field.resize(10, std::vector<char>(10, NOTHING_CHAR));
    _opponent_field.resize(10, std::vector<char>(10, NOTHING_CHAR));
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

std::pair<int, int> Player::shot(int result) {
    ++_shotsCount;

    _last_shot =
}

//0 - не попал
//1 - попал
//2 - убил
int Player::opponent_shot(const std::pair<int, int> &coords) {
    auto [x, y] = coords;

    if (field[y][x] == NOTHING_CHAR)
        return Result::MISS;

    if (field[y][x] == SHIP_CHAR && check_cage(coords)) {
        field[y][x] = SHOT_CHAR;
        return Result::KILL;
    }

    field[y][x] = SHOT_CHAR;
    int dx{}, dy{};
    for (int i = std::max(y - 1, 0); i <= std::min(y + 1, MAX_INDEX); i++) {
        for (int j = std::max(x - 1, 0); j <= std::min(x + 1, MAX_INDEX); j++) {
            if (i == x && j == y) continue;
            if (free_cage({j, i})) continue;
            if (field[i][j] == SHIP_CHAR) return Result::SHOT;
            dx = j - x;
            dy = i - y;
            int cx = j, cy = i;
            std::pair startShip{x, y}, endShip{x, y};
            while (field[cy][cx] != NOTHING_CHAR) {
                if (!(x + dx >= 0 && x + dx <= MAX_INDEX &&
                      y + dy >= 0 && y + dy <= MAX_INDEX)) {
                    break;
                }
                startShip = std::min(startShip, {cx, cy});
                endShip = std::max(endShip, {cx, cy});
                if (field[cy][cx] == SHIP_CHAR) {
                    return Result::SHOT;
                }
                cx += dx;
                cy += dy;
            }
        }
    }
    return Result::KILL;
}

bool Player::check_cage(const std::pair<int, int> &coords) {
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

bool Player::free_cage(const std::pair<int, int> &coords) {
    auto [x, y] = coords;
    return field[y][x] == NOTHING_CHAR || field[y][x] == MISS_CHAR;
}

void Player::kill_ship(const std::pair<int, int> &startShip, const std::pair<int, int> &endShip) {
    auto [startX, startY] = startShip;
    auto [endX, endY] = endShip;
    for (int i = std::max(startY - 1, 0); i <= std::min(endY + 1, 9); ++i) {
        for (int j = std::max(startX - 1, 0); j <= std::min(endX + 1, 9); ++j) {
            if ((i >= startY && i <= endY) && (j >= startX && j <= endX)) continue;
            _opponent_field[i][j] = MISS_CHAR;
        }
    }
}

bool Player::isMiss(const std::pair<int, int> &coords) {
    const auto &[x, y] = coords;
    return _opponent_field[y][x] == MISS_CHAR;
}

std::pair<int, int> Player::random_shot() {
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
    switch (result) {
        case Result::MISS:
            break;
        case Result::SHOT:
            break;
        case Result::KILL:
            break;
    }
}

}
