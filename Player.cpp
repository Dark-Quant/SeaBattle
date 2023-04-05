#include "Player.h"

Player::Player() : _random{} {}

std::vector<std::vector<char>> Player::create() {
    field.resize(10, std::vector<char>(10, '.'));

    unsigned startY, endY, startX, endX, direction, y, x;
    int dy, dx;

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

           for (y = _random(startY, endY); y != endY && y != UINT32_MAX; y += dy)
           {
               for (x = _random(startX, endX); x != endX && x != UINT32_MAX; x += dx)
               {
                   field[y][x] = 'X';
               }
           }
        }
    }
    // X - корабль
    // .....XXXX..
    //1 - 4палубный
    //2 - 3палубных
    //3 - 2палубных
    //4 - 1палубных
    return field;
}

std::pair<int, int> Player::shot() {
    return {0, 0};
}

int Player::opponent_shot(std::pair<int, int> p) {
    //0 - не попал
    //1 - попал
    //2 - убил
    return 0;
}