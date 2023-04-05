#include "Player.h"

int main() {
    Player player;
    auto f = player.create();

    while (std::cin.get()) {
        auto [x, y] = player.shot(0);
        player._opponent_field[y][x] = 'M';
        for (const auto &i: player._opponent_field) {
            for (auto j: i) {
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
    }
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