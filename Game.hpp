#pragma once

#include <bits/stdc++.h>
#include <windows.h>
#include "PlayerRandom.hpp"

struct Game {
    vector<int> dx = {1, 1, 1, -1, -1, -1, 0, 0, 0};
    vector<int> dy = {1, 0, -1, 1, 0, -1, 1, 0, -1};
    int dk = 9;

    void print_field(vector<vector<char>> &field) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                cout << field[i][j];
            }
            cout << endl;
        }
    }

    bool check(int x, int y) {
        return x >= 0 && x < 10 && y >= 0 && y < 10;
    }

    void kill(int x, int y, vector<vector<char>> &field) {
        int x1 = x, x2 = x, y1 = y, y2 = y;
        while (x1 > 0 && field[x1 - 1][y1] == 'P') x1--;
        while (x2 < 9 && field[x2 + 1][y1] == 'P') x2++;
        while (y1 > 0 && field[x1][y1 - 1] == 'P') y1--;
        while (y2 < 9 && field[x1][y2 + 1] == 'P') y2++;

        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                for (int k = 0; k < dk; k++) {
                    if (check(i + dx[k], j + dy[k]) && field[i + dx[k]][j + dy[k]] == '.') {
                        field[i + dx[k]][j + dy[k]] = '*';
                    }
                }
            }
        }
        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                field[i][j] = 'K';
            }
        }
    }


    void game(IPlayer &p1, IPlayer &p2) {
        vector<vector<char>> field_p1, field_p2;

        field_p1 = p1.create();
        field_p2 = p2.create();

        int turn = 0;


        turn = rand() % 2;
        int kill_p1 = 0, kill_p2 = 0;

        while (kill_p1 < 10 && kill_p2 < 10) {
            cout << "before" << endl;
            cout << p1.team_name() << endl << endl;
            print_field(field_p1);
            cout << endl << endl << endl;
            cout << p2.team_name() << endl << endl;
            print_field(field_p2);

            cout << "after" << endl;
            if (turn == 0) {
                pair<int, int> shot = p1.shot();
                int res = p2.opponent_shot(shot);
                p1.get_shot_res(res);
                if (res == 0) {
                    turn = 1;
                    if (field_p2[shot.first][shot.second] == '.')
                        field_p2[shot.first][shot.second] = '*';
                }
                if (res == 1) {
                    field_p2[shot.first][shot.second] = 'P';
                }
                if (res == 2) {
                    field_p2[shot.first][shot.second] = 'P';
                    kill(shot.first, shot.second, field_p2);
                    kill_p1++;
                }
                cout << shot.first << " " << shot.second << " " << turn << endl;
            } else {
                pair<int, int> shot = p2.shot();
                int res = p1.opponent_shot(shot);
                p2.get_shot_res(res);
                if (res == 0) {
                    if (field_p1[shot.first][shot.second] == '.')
                        field_p1[shot.first][shot.second] = '*';
                    turn = 0;
                }
                if (res == 1) {
                    field_p1[shot.first][shot.second] = 'P';
                }
                if (res == 2) {
                    field_p1[shot.first][shot.second] = 'P';
                    kill(shot.first, shot.second, field_p1);
                    kill_p2++;
                }
                cout << shot.first << " " << shot.second << " " << turn << endl;
            }

            COORD coord;
            coord.X = 0;
            coord.Y = 0;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            Sleep(50);

        }


        cout << p1.team_name() << endl << endl;
        print_field(field_p1);
        cout << endl << endl << endl;
        cout << p2.team_name() << endl << endl;
        print_field(field_p2);

    }

};
