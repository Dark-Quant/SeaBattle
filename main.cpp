#include "Player.h"

int main() {
    Player player;
    auto f = player.create();

    player._opponent_field[3][0] = 'S';
    player._opponent_field[3][1] = 'S';
    player._opponent_field[3][2] = 'S';
    for (const auto &i: player._opponent_field) {
        for (auto j: i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }

    auto [start, end] = player.get_opponent_ship({1, 3});

    std::cout << start.first << ' ' << start.second << std::endl <<
    end.first << ' ' << end.second << std::endl;

//    for (int i = 0; i < 10; ++i)
//    {
//        int x{}, y{};
//        std::cin >> x >> y;
//        switch (player.opponent_shot({x, y}))
//        {
//            case Player::Result::MISS:
//                std::cout << "MISS";
//                break;
//            case Player::Result::SHOT:
//                std::cout << "SHOT";
//                break;
//            case Player::Result::KILL:
//                std::cout << "KILL";
//                break;
//        }
//        std::cout << std::endl;
//    }
    return 0;
}