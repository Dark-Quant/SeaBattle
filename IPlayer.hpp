#pragma once
#include <bits/stdc++.h>


using namespace std;


struct IPlayer {
    virtual vector<vector<char> > create() {};
    virtual pair<int, int> shot() {};
    virtual int opponent_shot(pair<int, int> p) {};
    virtual void get_shot_res(int res) {};
    virtual string team_name() {};
};
