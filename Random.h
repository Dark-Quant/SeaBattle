#pragma once

#include <random>

template<typename T>
class Random {
public:
    Random();

    T operator()(const T &a, const T &b);

private:
    std::mt19937 _generator;
    std::mt19937::result_type _seed;
    std::random_device _randomDevice;
};

#include "Random.tpp"