#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define Exceed_Upper_Bound 0
#define VALID 1

class tetris {
    public :
        bool shape[4][4] = {0};

        tetris(string s) {
            switch(s[0]) {
                case 'T' : if (s[1] == '1') {shape[2][0] = 1; shape[2][1] = 1; shape[2][2] = 1; shape[3][1] = 1; break;}
                           else if (s[1] == '2') {shape[1][1] = 1; shape[2][0] = 1; shape[2][1] = 1; shape[3][1] = 1; break;}
                           else if (s[1] == '3') {shape[2][1] = 1; shape[3][0] = 1; shape[3][1] = 1; shape[3][2] = 1; break;}
                           else {shape[1][0] = 1; shape[2][0] = 1; shape[2][1] = 1; shape[3][0] = 1; break;}
                case 'L' : if (s[1] == '1') {shape[1][0] = 1; shape[2][0] = 1; shape[3][0] = 1; shape[3][1] = 1; break;}
                           else if (s[1] == '2') {shape[2][0] = 1; shape[2][1] = 1; shape[2][2] = 1; shape[3][0] = 1; break;}
                           else if (s[1] == '3') {shape[1][0] = 1; shape[1][1] = 1; shape[2][1] = 1; shape[3][1] = 1; break;}
                           else {shape[2][2] = 1; shape[3][0] = 1; shape[3][1] = 1; shape[3][2] = 1; break;}
                case 'J' : if (s[1] == '1') {shape[1][1] = 1; shape[2][1] = 1; shape[3][0] = 1; shape[3][1] = 1; break;}
                           else if (s[1] == '2') {shape[2][0] = 1; shape[3][0] = 1; shape[3][1] = 1; shape[3][2] = 1; break;}
                           else if (s[1] == '3') {shape[1][0] = 1; shape[1][1] = 1; shape[2][0] = 1; shape[3][0] = 1; break;}
                           else {shape[2][0] = 1; shape[2][1] = 1; shape[2][2] = 1; shape[3][2] = 1; break;}
                case 'S' : if (s[1] == '1') {shape[2][1] = 1; shape[2][2] = 1; shape[3][0] = 1; shape[3][1] = 1; break;}
                           else {shape[1][0] = 1; shape[2][0] = 1; shape[2][1] = 1; shape[3][1] = 1; break;}
                case 'Z' : if (s[1] == '1') {shape[2][0] = 1; shape[2][1] = 1; shape[3][1] = 1; shape[3][2] = 1; break;}
                           else {shape[1][1] = 1; shape[2][0] = 1; shape[2][1] = 1; shape[3][0] = 1; break;}
                case 'I' : if (s[1] == '1') {shape[0][0] = 1; shape[1][0] = 1; shape[2][0] = 1; shape[3][0] = 1; break;}
                           else {shape[3][0] = 1; shape[3][1] = 1; shape[3][2] = 1; shape[3][3] = 1; break;}
                case 'O' : shape[2][0] = 1; shape[2][1] = 1; shape[3][0] = 1; shape[3][1] = 1;
            }
        }
};

bool drop(bool **, tetris, int, int, int, int);
void fill(bool **, tetris, int, int, int);
void elimination(bool **, int, int);

int main(void)
{
    fstream fin;
    fstream fout;
    int rows, cols;
    bool **Background;
    string s;
    int initial_col, move_step;
    bool judge = VALID;

    fin.open("C:\\Users\\User\\Desktop\\Project1\\2.data", ios::in);
    fin >> rows >> cols;

    Background = new bool * [rows];
    for (int i = 0; i < rows; i++)
        Background[i] = new bool [cols]();

    for (fin >> s; s != "End" && judge == VALID; fin >> s) {
        tetris dropping_tetris(s);

        fin >> initial_col >> move_step;
        initial_col--;
        judge = drop(Background, dropping_tetris, initial_col, move_step, rows, cols);
    }

    fin.close();

    fout.open("C:\\Users\\User\\Desktop\\Project1\\tetris.final.txt", ios::out);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            fout << Background[i][j] << ' ';
        fout << endl;
    }

    fout.close();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) cout << Background[i][j] << ' ';
        cout << endl;
    }

    for (int i = 0; i < rows; i++)
        delete [] Background[i];
    delete [] Background;

    return 0;
}

bool drop(bool **Background, tetris Tetris, int initial_col, int move_step, int rows, int cols) {
    int final_col = initial_col + move_step;
    int distance[3];
    int dis_in_backgnd;         // distance in background
    int dis_in_tetris;          // distance in tetris
    int min_dis_col;            // the column of minimum distance
    int ref_row;                // (ref_row, final_col) is the coordinate of the reference point after dropping
    int max_height_tetris = -1;

    // calculate the distance of each column of tetris
    int index = 0;
    int tetris_row;
    for (int tetris_col = 0; tetris_col < 4; tetris_col++, index++) {
        for (dis_in_backgnd = 0; dis_in_backgnd < rows && Background[dis_in_backgnd][initial_col + tetris_col] == 0
            ; dis_in_backgnd++);
        for (tetris_row = 3, dis_in_tetris = 0; Tetris.shape[tetris_row][tetris_col] == 0 && tetris_row > 0; 
            dis_in_tetris++, tetris_row--);
        distance[tetris_col] = dis_in_backgnd + dis_in_tetris;
        if (tetris_row == 0 && Tetris.shape[tetris_row][tetris_col] == 0) distance[tetris_col] = -1;
    }

    // find the column of minimum distance
    int j_col;
    for (j_col = 1, min_dis_col = 0; j_col < 4; j_col++) {
        if (distance[j_col] < distance[min_dis_col] && distance[j_col] != -1) min_dis_col = j_col;
    }

    // find the coordinate of the reference point and fill the background
    ref_row = distance[min_dis_col] - 1;
    int tmp = ref_row;
    for (int tetris_col = 0, index = 0; tetris_col < 4; tetris_col++, index++) {
        for (dis_in_backgnd = 0; dis_in_backgnd < (rows - 1) - tmp && Background[dis_in_backgnd + tmp + 1][final_col + tetris_col] == 0
            ; dis_in_backgnd++);
        for (tetris_row = 3, dis_in_tetris = 0; Tetris.shape[tetris_row][tetris_col] == 0 && tetris_row > 0; 
            dis_in_tetris++, tetris_row--);
        distance[tetris_col] = dis_in_backgnd + dis_in_tetris;
        if (tetris_row == 0 && Tetris.shape[tetris_row][tetris_col] == 0) distance[tetris_col] = -1;
    }
    for (j_col = 1, min_dis_col = 0; j_col < 4; j_col++) {
        if (distance[j_col] < distance[min_dis_col] && distance[j_col] != -1) min_dis_col = j_col;
    }
    ref_row += distance[min_dis_col];
    fill(Background, Tetris, ref_row, final_col, cols);

    // find the maximum height of tetris
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            if (Tetris.shape[i][j] == 1) {
                max_height_tetris = 4 - i;
                break;
            }
        if (max_height_tetris != -1) break;
    }
    if (ref_row + 1 - max_height_tetris < 0)
        return Exceed_Upper_Bound;

    // do the elimination
    elimination(Background, rows, cols);

    return VALID;
}

void fill(bool **Background, tetris Tetris, int ref_row, int final_col, int cols) {
    int i, j, which_col;

    for (which_col = 3; final_col + which_col > cols - 1; which_col--);
    for (i = 3; i >= 0 && ref_row - 4 + i >= 0; i--)
        for (j = which_col; j >= 0; j--) {
            Background[ref_row - 3 + i][final_col + j] += Tetris.shape[i][j];
        }
}

void elimination(bool **Background, int rows, int cols) {
    vector<int> eli_row;        // the index of eliminated rows

    // find which rows should be eliminated
    for (int i = rows - 1; i >= 0; i--) {
        for (int j = cols - 1; j >= 0; j--) {
            if (Background[i][j] == 0)
                break;
            if (j == 0 && Background[i][j] == 1)
                eli_row.push_back(i);
        }
    }

    // drop the remaining rows
    if (eli_row.size() != 0) {
        int need_filled = eli_row[0];
        int fill = need_filled - 1;
        for (int index = 1; need_filled >= 0; need_filled--, fill--) {
            for ( ; index < eli_row.size() && fill == eli_row[index]; fill--, index++);
            if (fill < 0)
                for (int j = 0; j < cols; j++) Background[need_filled][j] = 0;
            else
                for (int j = 0; j < cols; j++) Background[need_filled][j] = Background[fill][j];
        }
    }
}