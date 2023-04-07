#pragma once
#include <bits/stdc++.h>

using namespace std;


struct CheckPlayer {
    vector<vector<char> > field;
    vector<int> dx = {1, 1, 1, -1, -1, -1, 0, 0, 0};
    vector<int> dy = {1, 0, -1, 1, 0, -1, 1, 0, -1};
    vector<int> ships = {0, 0, 0, 0};
    pair<int, int> last_shot = {-1, -1};
    int dk = 9;
    int x1, x2, y1, y2;

    CheckPlayer() = default;

    bool check(int x, int y) {
        return x >= 0 && x < 10 && y >= 0 && y < 10;
    }

    bool check_empty(int x, int y) {
        return check(x, y) && field[x][y] == '.' || !check(x, y);
    }


    bool check_ship(int x, int y, int &cnt) {
        cnt++;
        field[x][y] = '.';
        x1 = min(x1, x);
        y1 = min(y1, y);
        x2 = max(x2, x);
        y2 = max(y2, y);
        if (check(x + 1, y) && field[x + 1][y] == 'X') check_ship(x + 1, y, cnt);
        if (check(x - 1, y) && field[x - 1][y] == 'X') check_ship(x - 1, y, cnt);
        if (check(x, y + 1) && field[x][y + 1] == 'X') check_ship(x, y + 1, cnt);
        if (check(x, y - 1) && field[x][y - 1] == 'X') check_ship(x, y - 1, cnt);

    }

    bool create(vector<vector<char> > pfield) {
        field = pfield;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (field[i][j] == '.') continue;
                if (field[i][j] != 'X') return false;
                int cnt = 0;
                x1 = 10;
                x2 = 0;
                y1 = 10;
                y2 = 0;
                check_ship(i, j, cnt);
                if (x1 - x2 != 0 && y1 - y2 != 0) return false;
                if (cnt < 1 || cnt > 4) return false;
                for (int k = 0; k < dk; k++) {
                    if (check(i + dx[k], j + dy[k]) && field[i + dx[k]][j + dy[k]] != '.') {
                        return false;
                    }
                }
                ships[cnt - 1]++;
            }
        }
        field = pfield;
        return ships[0] == 4 && ships[1] == 3 && ships[2] == 2 && ships[3] == 1;
    }


    bool shot(pair<int, int> p){
        return p.first >= 0 && p.first < 10 && p.second >= 0 && p.second < 10;
    }

    bool opponent_shot(pair<int, int> p, int res){
        int x = p.first;
        int y = p.second;
        if (field[x][y] != 'X') {
            return 0 == res;
        }
        field[x][y] = 'P';
        int x1 = x, x2 = x, y1 = y, y2 = y;
        while(x1 > 0 && field[x1 - 1][y1] == 'P') x1--;
        while(x2 < 9 && field[x2 + 1][y1] == 'P') x2++;
        while(y1 > 0 && field[x1][y1 - 1] == 'P') y1--;
        while(y2 < 9 && field[x1][y2 + 1] == 'P') y2++;

        for (int k = 0; k < dk; k++) {
            if (check(x1 + dx[k], y1 + dy[k]) && field[x1 + dx[k]][y1 + dy[k]] == 'X') {
                return 1 == res;
            }
            if (check(x2 + dx[k], y2 + dy[k]) && field[x2 + dx[k]][y2 + dy[k]] == 'X') {
                return 1 == res;
            }
        }

        return 2 == res;

        //0 - �� �����
        //1 - �����
        //2 - ����
    }

    string team_name(){
        return "Random Player";
    }

};