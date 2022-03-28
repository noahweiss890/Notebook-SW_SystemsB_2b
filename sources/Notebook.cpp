#include "Notebook.hpp"
#include "Direction.hpp"
#include <iostream>
#include <unordered_map>
#include <string>
#include <limits.h>
using namespace ariel;
using namespace std;
using ariel::Direction;


namespace ariel{
    static const int page_width = 100;
    static const int min_char = 32;
    static const int max_char = 126;
    static const int max_digit = 9;
    static const int ten = 10;
    static const int spacing_amount = 5;

    void Notebook::write(int page, int row, int column, Direction direction, string text) {
        if(page < 0 || column < 0 || row < 0 || column >= page_width || (direction == Direction::Horizontal && column + (int)text.length() > page_width)) {
            throw invalid_argument("illegal arguments! write");
        }
        for(size_t i = 0; i < text.length(); i++) {
            if((int)text.at(i) < min_char || (int)text.at(i) > 126 || text.at(i) == '~') {
                throw invalid_argument("illegal text!");
            }
        }
        string emp;
        for(int i = 0; i < text.length(); i++) {
            emp += "_";
        }

        string temp = this->read(page, row, column, direction, (int)text.length());
        if(temp != emp) {
            throw invalid_argument("cannot write here!");
        }

        for(size_t i = 0; i < text.length(); i++) {
            if(direction == Direction::Horizontal) {
                this->nbook[page][row][column + (int)i] = text.at(i);
            }
            else {
                this->nbook[page][row + (int)i][column] = text.at(i);
            }
        }
    }

    string Notebook::read(int page, int row, int column, Direction direction, int length) {
        if(page < 0 || column < 0 || row < 0 || length < 0 || column >= page_width || (direction == Direction::Horizontal && column + length > page_width)) {
            throw invalid_argument("illegal arguments! read");
        }
        string str;
        for(int i = 0; i < length; i++) {
            if(direction == Direction::Horizontal) {
                if(this->nbook[page][row][column + i] == '\0') {
                    str += "_";
                }
                else {
                    str += this->nbook[page][row][column + i];
                }
            }
            else {
                if(this->nbook[page][row + i][column] == '\0') {
                    str += "_";
                }
                else {
                    str += this->nbook[page][row + i][column];
                }
            }
        }
        return str;
    }

    void Notebook::erase(int page, int row, int column, Direction direction, int length) {
        if(page < 0 || column < 0 || row < 0 || length < 0 || column >= page_width || (direction == Direction::Horizontal && column + length > page_width)) {
            throw invalid_argument("illegal arguments! earse");
        }
        for(int i = 0; i < length; i++) {
            if(direction == Direction::Horizontal) {
                this->nbook[page][row][column + i] = '~';
            }
            else {
                this->nbook[page][row + i][column] = '~';
            }
        }
    }

    void Notebook::show(int page) {
        if(page < 0) {
            throw invalid_argument("cant have negitive page number!");
        }
        int max_row = 0;
        int min_row = INT_MAX;
        for(auto const row: this->nbook[page]) {
            if(row.first > max_row) {
                max_row = row.first;
            }
            if(row.first < min_row) {
                min_row = row.first;
            }
        }
        for(int i = max(min_row - 2, 0); i < max_row + 3; i++) {
            int num = i;
            int digits = 1;
            while(num > max_digit) {
                digits++;
                num /= ten;
            }
            cout << i << ":";
            for(int k = digits; k < spacing_amount; k++) {
                cout << " ";
            }
            for(int j = 0; j < page_width; j++) {
                if(this->nbook[page][i][j] == '\0') {
                    cout << "_";
                }
                else {
                    cout << this->nbook[page][i][j];
                }
            }
            cout << endl;
        }
        cout << endl << endl;
    }
}