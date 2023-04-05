#include "Player.h"

int main()
{
    Player player;
    auto f = player.create();

    for (auto i : f)
    {
        for (auto j : i)
        {
            std::cout << j;
        }
        std::cout << std::endl;
    }
//    std::random_device rd;
//    std::mt19937::result_type _seed = rd() ^ (
//            (std::mt19937::result_type)
//                    std::chrono::duration_cast<std::chrono::seconds>(
//                            std::chrono::system_clock::now().time_since_epoch()
//                    ).count() +
//            (std::mt19937::result_type)
//                    std::chrono::duration_cast<std::chrono::microseconds>(
//                            std::chrono::high_resolution_clock::now().time_since_epoch()
//                    ).count() );
//
//    std::mt19937 gen(_seed);
//    std::uniform_int_distribution<unsigned> _distrib(1, 6);
//
//    for( unsigned long j = 0; j < 100500; ++j )
//    {
//        std::cout << _distrib(gen) << ' ';
//    }
//
//    std::cout << '\n';
    return 0;
}