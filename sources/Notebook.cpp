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
    // defining constants
    static const int page_width = 100;
    static const int min_char = 32;
    static const int max_char = 126;
    static const int max_digit = 9;
    static const int ten = 10;
    static const int spacing_amount = 5;

    // function for writing in the notbook
    void Notebook::write(int page, int row, int column, Direction direction, string text) {
        // check if the input is legal
        if(page < 0 || column < 0 || row < 0 || column >= page_width || (direction == Direction::Horizontal && column + (int)text.length() > page_width)) {
            throw invalid_argument("illegal arguments! write");
        }
        // check if the text is legal
        for(size_t i = 0; i < text.length(); i++) {
            if((int)text.at(i) < min_char || (int)text.at(i) > max_char || text.at(i) == '~') {
                throw invalid_argument("illegal text!");
            }
        }
        string emp;
        // build a string to check if the notbook at the given location is empty
        for(int i = 0; i < text.length(); i++) {
            emp += "_";
        }
        // read the notbebook at the given location
        string temp = this->read(page, row, column, direction, (int)text.length());
        // check if there is something already written in the given location in the notebook
        if(temp != emp) {
            throw invalid_argument("cannot write here!");
        }
        // here we actually write in the notebook
        for(size_t i = 0; i < text.length(); i++) {
            // check which direction to write in
            if(direction == Direction::Horizontal) {
                this->nbook[page][row][column + (int)i] = text.at(i);
            }
            else {
                this->nbook[page][row + (int)i][column] = text.at(i);
            }
        }
    }

    // function for reading the notebook
    string Notebook::read(int page, int row, int column, Direction direction, int length) {
        // check if the input is legal
        if(page < 0 || column < 0 || row < 0 || length < 0 || column >= page_width || (direction == Direction::Horizontal && column + length > page_width)) {
            throw invalid_argument("illegal arguments! read");
        }
        string str; // this will hold what is written in the notbook at the given location
        for(int i = 0; i < length; i++) {
            // check which direction to read in
            if(direction == Direction::Horizontal) {
                // if there is nothing written there, add a "_"
                if(this->nbook[page][row][column + i] == '\0') {
                    str += "_";
                }
                else {
                    str += this->nbook[page][row][column + i];
                }
            }
            else {
                // if there is nothing written there, add a '~'
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

    // function for erasing text in the notebook
    void Notebook::erase(int page, int row, int column, Direction direction, int length) {
        // check if the input is legal
        if(page < 0 || column < 0 || row < 0 || length < 0 || column >= page_width || (direction == Direction::Horizontal && column + length > page_width)) {
            throw invalid_argument("illegal arguments! earse");
        }
        // go through the given location and write '~'
        for(int i = 0; i < length; i++) {
            // check which direction to go in
            if(direction == Direction::Horizontal) {
                this->nbook[page][row][column + i] = '~';
            }
            else {
                this->nbook[page][row + i][column] = '~';
            }
        }
    }

    // fuction that shows the content of a given page in the notebook
    void Notebook::show(int page) {
        // check if the page number in legal
        if(page < 0) {
            throw invalid_argument("cant have negitive page number!");
        }
        int max_row = 0;
        int min_row = INT_MAX;
        // fins the max and min row numbers
        for(auto const &row: this->nbook[page]) {
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
            // find out how many digits there are in the row number
            while(num > max_digit) {
                digits++;
                num /= ten;
            }
            cout << i << ":";
            for(int k = digits; k < spacing_amount; k++) {
                cout << " ";
            }
            // prints out the content of the row
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