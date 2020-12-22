#include <math.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void findAirplaneSeat(string, int, int, int&);
void addTicket(int[], const int);

void print2DArray(int[128][8]);

int main(int argc, char* argv[]) {
    ifstream file;
    // file.open("testing5.txt");
    file.open("binarySeating.txt");

    int seats[128][8] = {};

    // STL priority_queue functions as max_heap with default parameters
    int maxID = 0, ourID = 0;

    string line;
    while (getline(file, line) && !file.eof()) {
        int row = 0, col = 0;
        // Get the row
        findAirplaneSeat(line.substr(0, line.length() - 3), 0, 127, row);
        // Get the col
        findAirplaneSeat(line.substr(line.length() - 3), 0, 7, col);

        int seatID = row * 8 + col;
        seats[row][col] = seatID;

        if (seatID > maxID) maxID = seatID;
        // cout << "Row: " << row << "; Col: " << col << "; ID: " << seatID <<
        // endl;
    }

    cout << "Part 1 > " << maxID << endl;

    // Used to find the missing seat, and it's ID
    print2DArray(seats);

    cout << "Part 2 > " << ourID << endl;
    file.close();
    return 0;
}

void print2DArray(int seats[128][8]) {
    for(int r = 0; r < 128; r++) {
        for(int c = 0; c < 8; c++) {
            cout << seats[r][c] << " ";
        }
        cout << endl;
    }
}

void findAirplaneSeat(string ticket, int beg, int end, int& seat) {
    if (!ticket.length()) {
        return;
    } else {
        char binPos = ticket[0];
        if (binPos == 'F' || binPos == 'L') {
            seat = floor((beg + end) / 2.0);
            end = seat;
        } else if (binPos == 'B' || binPos == 'R') {
            seat = ceil((beg + end) / 2.0);
            beg = seat;
        } else {
            cout << "Something went wrong?" << endl;
            // Invalid seat pos
        }
    }
    findAirplaneSeat(ticket.substr(1), beg, end, seat);
}
