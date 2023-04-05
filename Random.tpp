#include "Random.h"

#include <chrono>

template<typename T>
Random<T>::Random() : _randomDevice{} {
    _seed = _randomDevice() ^ (
            static_cast<std::mt19937::result_type>(
                    std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::system_clock::now().time_since_epoch()
                    ).count()) +
            static_cast<std::mt19937::result_type>(
                    std::chrono::duration_cast<std::chrono::microseconds>(
                            std::chrono::high_resolution_clock::now().time_since_epoch()
                    ).count()));
    _generator.seed(_seed);
}

template<typename T>
T Random<T>::operator()(const T &a, const T &b) {
    std::uniform_int_distribution<T> distrib(a, b);
    return distrib(_generator);
}
